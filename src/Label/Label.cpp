#include "Label/Label.h"
#include <cmath>
#include "ResourceManager/ResourceManager.h"

const float DEFAULT_TEXT_SIZE = 0.05f;

Label::Label(std::string text, double diametr, Magnum::Vector3 coords)
    : text(text)
    , diametr(diametr)
    , coords(coords)
    , text_mesh{Magnum::NoCreate}
    , visible(true)
    , scale(-1)
{}

int Label::get_scale()
{
    return scale;
}

void Label::set_scale(float scale)
{
    this->scale = scale;
    visible = (diametr > 10 * (15 - scale * 15 / 8.5));
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dz = z1 - z2;
    return (float)sqrt(dx*dx + dy*dy + dz*dz);
}

bool Label::is_visible()
{
    return visible;
}

bool Label::on_camera(const Camera &c)
{
    Magnum::Vector3 from_camera_to_label =
            Vector3(coords.x() - c.x, coords.y() - c.y, coords.z() - c.z);
    Magnum::Vector3 from_camera_to_center = Vector3(-c.x, -c.y, -c.z);

    from_camera_to_label= from_camera_to_label.normalized();
    from_camera_to_center = from_camera_to_center.normalized();

    Magnum::Math::Rad<float> angle = Magnum::Math::angle(from_camera_to_label, from_camera_to_center);
    Magnum::Math::Deg<float> angle_deg = Magnum::Math::Deg<float>(angle);

    auto l = coords;
    if (angle_deg < 17.0_degf &&
        distance(c.x, c.y, c.z, 0, 0, 0) < distance(c.x, c.y, c.z, l.x(), l.y(), l.z()))
    {
        return true;
    } else {
        return false;
    }

    // всего 15 уровней диаметра, 10,20,30,...,150 км
    // scala_k от 1 до 9.5, поэтому 15/8.5
}

void Label::set_font(std::shared_ptr<Magnum::Text::AbstractFont>& font,
                    Magnum::Text::DistanceFieldGlyphCache& cache)
{
    set_font(1, font, cache);
}

void Label::set_font(float scale, std::shared_ptr<Magnum::Text::AbstractFont>& font,
                    Magnum::Text::DistanceFieldGlyphCache& cache)
{
    std::tie(text_mesh, std::ignore) = Magnum::Text::Renderer3D::render(
        *font,
        cache,
        DEFAULT_TEXT_SIZE / pow(scale, scale / 7),
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
    Vector3 target_direction = coords; // нужное направление перпендикуляра к поверхности
                                            // т.е все матрицы смотрят на центр сферы

    direction = direction.normalized();
    target_direction = target_direction.normalized();

    if (target_direction == Magnum::Vector3{0, 0, 0})
        return {};
    Magnum::Math::Rad<float> angle = Magnum::Math::angle(direction, target_direction);
    // осью поворота является векторное произведение текущего и нужного направлений
    // Vector3 axis = Magnum::Math::cross(target_direction, direction);
    Vector3 axis = Magnum::Math::cross(direction, target_direction);
    // Error() << axis << "keeeeeek\n";

    axis = axis.normalized();

    auto rotation = Magnum::Matrix4::rotation(angle, axis);

    return rotation;

    return {};
}

void Label::draw(Magnum::Shaders::DistanceFieldVector3D& shader,
                 Magnum::Text::DistanceFieldGlyphCache& cache,
                 Magnum::Matrix4 global_state)
{
    Renderer::enable(Renderer::Feature::Blending);
    Renderer::setBlendFunction(Renderer::BlendFunction::SourceAlpha,
                               Renderer::BlendFunction::OneMinusSourceAlpha);
    Renderer::setBlendEquation(Renderer::BlendEquation::Add, Renderer::BlendEquation::Add);

    Magnum::Matrix4 rotation = calc_good_local_state(coords);
    Magnum::Matrix4 translation = Magnum::Matrix4::translation(coords);


    shader.setTransformationProjectionMatrix(
        global_state * translation * rotation);
    shader.setVectorTexture(cache.texture())
        .setColor(Color4::fromHsv(216.0_degf, 0.85f, 1.0f, 0.95f))
        .setOutlineColor(Color3{0.95f});
    text_mesh.draw(shader);

    Renderer::disable(Renderer::Feature::Blending);
}
