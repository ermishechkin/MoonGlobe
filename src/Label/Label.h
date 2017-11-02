#ifndef LABEL_H
#define LABEL_H

#include <Magnum/Mesh.h>
#include <Magnum/Renderer.h>
#include <Magnum/Shaders/DistanceFieldVector.h>
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>
#include <Magnum/Text/Renderer.h>

#include <string>
#include <memory>
#include <tuple>

using namespace Magnum;

class Label
{
public:
    Label(std::string text);

    void setFont(std::unique_ptr<Magnum::Text::AbstractFont>& font,
                 Magnum::Text::DistanceFieldGlyphCache& cache);
    void draw(Magnum::Shaders::DistanceFieldVector3D& shader,
              Magnum::Text::DistanceFieldGlyphCache& cache);

private:
    std::string text;
    Magnum::Mesh text_mesh;
    Magnum::Buffer vertices;
    Magnum::Buffer indices;

    // Magnum::Matrix3 _transformation;
    // Magnum::Matrix3 _projection;
};


#endif
