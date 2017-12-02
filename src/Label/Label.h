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

#include "Utils/MeshGenerators.h"
#include "Camera/Camera.h"

using namespace Magnum;

class Label
{
public:
    Label(std::string text, double diametr, Magnum::Vector3 coords);

    void set_font(float scale, std::shared_ptr<Magnum::Text::AbstractFont>& font,
                  Magnum::Text::DistanceFieldGlyphCache& cache);
    void set_font(std::shared_ptr<Magnum::Text::AbstractFont>& font,
                  Magnum::Text::DistanceFieldGlyphCache& cache);
    void draw(Magnum::Shaders::DistanceFieldVector3D& shader,
              Magnum::Text::DistanceFieldGlyphCache& cache,
              Magnum::Matrix4 global_state);

    bool is_visible();
    bool on_camera(const Camera &camera);
    int get_scale();
    void set_scale(float scale);

    Label() = delete;
    Label(const Label&) = delete;
    Label operator = (const Label&) = delete;

private:

    double diametr;
    bool visible;
    std::string text;
    Magnum::Vector3 coords;
    Magnum::Matrix4 state;
    Magnum::Mesh text_mesh;
    Magnum::Buffer vertices;
    Magnum::Buffer indices;
    float scale;

};


#endif
