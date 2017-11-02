#include "Label/Label.h"

Label::Label(std::string text)
    : text(text)
{}

void Label::setFont(std::unique_ptr<Magnum::Text::AbstractFont>& font,
                    Magnum::Text::DistanceFieldGlyphCache& cache)
{
    std::tie(text_mesh, std::ignore) = Magnum::Text::Renderer3D::render(
        *font,
        cache,
        0.1f,
        text,
        vertices,
        indices,
        Magnum::BufferUsage::StaticDraw,
        Magnum::Text::Alignment::MiddleCenter
    );

}

void Label::draw(Magnum::Shaders::DistanceFieldVector3D& shader,
                 Magnum::Text::DistanceFieldGlyphCache& cache)
{
    shader.setVectorTexture(cache.texture());

   // _shader.setTransformationProjectionMatrix(_projection * _transformation)
       shader.setColor(Magnum::Color3::fromHsv(216.0_degf, 0.85f, 1.0f))
       .setOutlineColor(Magnum::Color3{0.95f})
       .setOutlineRange(0.45f, 0.35f);
    //    .setSmoothness(0.025f/ _transformation.uniformScaling());
   text_mesh.draw(shader);
}
