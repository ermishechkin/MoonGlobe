#include "Label/Label.h"
#include "ResourceManager/ResourceManager.h"

Label::Label(std::string text, double diametr, Magnum::Vector3 coords)
    : text(text)
    , diametr(diametr)
    , coords(coords)
    , text_mesh{Magnum::NoCreate}
{}

bool Label::is_visible()
{
    return diametr > 80;
}

void Label::setFont(std::shared_ptr<Magnum::Text::AbstractFont>& font,
                    Magnum::Text::DistanceFieldGlyphCache& cache)
{
    std::tie(text_mesh, std::ignore) = Magnum::Text::Renderer3D::render(
        *font,
        cache,
        0.05f,
        text,
        vertices,
        indices,
        Magnum::BufferUsage::StaticDraw,
        Magnum::Text::Alignment::MiddleCenter
    );
}

/* каждая надпись должна быть плоскостью перпендикулярна поверности сферы
   поэтому ее нужно правильно повернуть
   функция возвращает нужную матрицу поворота
*/
Magnum::Matrix4 calc_good_local_state(Magnum::Vector3 coords)
{
    Vector3 direction = {0, 0, 1}; // так всегда, т.к меш из рендерара перпедикулярен оси z
    Vector3 target_direction = -1 * coords; // нужное направление перпендикуляра к поверхности
                                            // т.е все матрицы смотрят на центр сферы

                                            Error() << target_direction << "\n";
    // normalize(direction);
    // normalize(target_direction);
    direction = direction.normalized();
    target_direction = target_direction.normalized();

    if (target_direction == Magnum::Vector3{0, 0, 0})
        return Magnum::Matrix4{};
    Magnum::Math::Rad<float> angle = Magnum::Math::angle(direction, target_direction);
    // осью поворота является векторное произведение текущего и нужного направлений
    // Vector3 axis = Magnum::Math::cross(target_direction, direction);
    Vector3 axis = Magnum::Math::cross(direction, target_direction);
    Error() << axis << "keeeeeek\n";

    axis = axis.normalized();

    auto rotation = Magnum::Matrix4::rotation(angle, axis);

    return rotation;
}

void Label::draw(Magnum::Shaders::DistanceFieldVector3D& shader,
                 Magnum::Text::DistanceFieldGlyphCache& cache,
                 Magnum::Matrix4 global_state)
{
     Renderer::enable(Renderer::Feature::Blending);
     Renderer::setBlendFunction(Renderer::BlendFunction::SourceAlpha, Renderer::BlendFunction::OneMinusSourceAlpha);
     Renderer::setBlendEquation(Renderer::BlendEquation::Add, Renderer::BlendEquation::Add);

     Magnum::Matrix4 translation = Magnum::Matrix4::translation(coords);

     Magnum::Matrix4 rotation = calc_good_local_state(coords);


     shader.setTransformationProjectionMatrix(global_state * translation * rotation);
     shader.setVectorTexture(cache.texture())
           .setColor(Color4::fromHsv(216.0_degf, 0.85f, 1.0f, 0.95f));
     text_mesh.draw(shader);
}
