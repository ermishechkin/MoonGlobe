#include "MoonGlobeApplication.h"

using namespace Magnum;

const float CAMERA_BASE_DISTANCE = 10.0f;
static bool plugin_inited = false;

MoonGlobeApplication::MoonGlobeApplication()
    : shader{Shaders::Phong::Flag::DiffuseTexture},
      scaling(Matrix4::scaling({1.0, 1.0, 1.0})), scale_k(1), prev_scale(1), font_need_update(true), camera(0, 0, -CAMERA_BASE_DISTANCE)
{
    initProjectionMatrix();
    if (!plugin_inited) {
        plugin_inited = true;
    }
}

void MoonGlobeApplication::initProjectionMatrix()
{
    // set transform matrix
    transformation = Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
    // set perspective projection
    projection = Matrix4::perspectiveProjection(
        35.0_degf,
        Vector2{defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)
        * Matrix4::translation(Vector3::zAxis(-CAMERA_BASE_DISTANCE));
}

void MoonGlobeApplication::setShaderUniforms()
{
    // set shaders uniforms
    shader.setLightPosition({0.0f,1.0f, 20.0f})
        // .setDiffuseTexture(texture)
        .setLightColor(Color3{1.0f, 1.0f, 1.0f})
        .setTransformationMatrix(transformation * scaling)
        .setNormalMatrix(transformation.rotationScaling())
        .setProjectionMatrix(projection);
}

void MoonGlobeApplication::drawEvent()
{
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    if (font_need_update) {
        labels.set_scale(scale_k, camera);
        font_need_update = false;
    }

    setShaderUniforms();
    // shader.setDiffuseColor(Color4::fromHSV(216.0_degf, 0.85f, 1.0f));
    moon_globe.draw(shader, camera);
    // там внутри свой шейдер, нужны матрицы состояний
    labels.draw(transformation * scaling, projection, camera);
}

void MoonGlobeApplication::rotateEvent(float dx, float dy)
{
    const Vector2 delta = 3.0f *
                          Vector2{dx, dy} /
                          Vector2{defaultFramebuffer.viewport().size()};
    transformation = Matrix4::rotationX(Rad{delta.y()/scale_k}) *
                     Matrix4::rotationY(Rad{delta.x()/scale_k}) *
                     transformation;
    Vector4 cam{0, 0, -CAMERA_BASE_DISTANCE, 1};
    cam = transformation.inverted() * cam;
    cam = cam.normalized() * (CAMERA_BASE_DISTANCE - scale_k);
    camera.x = cam.x();
    camera.y = cam.y();
    camera.z = cam.z();
    font_need_update = true;
}

void MoonGlobeApplication::zoomEvent(float scale)
{
    scale_k += scale - 1.0;
    scale_k = scale_k > (CAMERA_BASE_DISTANCE-0.5f) ? (CAMERA_BASE_DISTANCE-0.5f) : scale_k;
    scale_k = scale_k < 0.5f ? 0.5f : scale_k;
//    camera.scale(scale_k);
    scaling = Matrix4::scaling({scale_k, scale_k, scale_k});

    Vector3d cam = Vector3d{camera.x, camera.y, camera.z};
    cam = cam.normalized() * (CAMERA_BASE_DISTANCE-scale_k);
    camera.x = cam.x(); camera.y = cam.y(); camera.z = cam.z();
    int prev_level = moon_globe.get_scale(), new_level;
    if (scale_k > 4) {
        new_level = 2;
    } else {
        new_level = 1;
    }
    moon_globe.set_scale(new_level);
    if (scale_k - prev_scale < -1 || scale_k - prev_scale > 1) {
        font_need_update = true;
        prev_scale = scale_k;
    }
}
