#include "PCMoonGlobeApplication.h"

using namespace Magnum;

const float CAMERA_BASE_DISTANCE = 10.0f;

PCMoonGlobeApplication::PCMoonGlobeApplication(const Arguments &arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("sphere")}
    , shader{Shaders::Phong::Flag::DiffuseTexture}
    , camera(0, 0, -CAMERA_BASE_DISTANCE)
    , scale_k(1)
{
    initProjectionMatrix();
}

void PCMoonGlobeApplication::initProjectionMatrix()
{
    // set transform matrix
    transformation = Matrix4::rotationX(0.0_degf) * Matrix4::rotationY(0.0_degf);
    // set perspective projection
    projection = Matrix4::perspectiveProjection(
        35.0_degf,
        Vector2{defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)
        * Matrix4::translation(Vector3::zAxis(camera.z));
}

void PCMoonGlobeApplication::setShaderUniforms()
{
    // set shaders uniforms
    shader.setLightPosition({0.0f,1.0f, 5.0f})
        .setDiffuseColor(Color3{1.0f, 1.0f, 0.0f})
        .setLightColor(Color3{1.0f, 1.0f, 1.0f})
        .setTransformationMatrix(transformation * scaling)
        .setNormalMatrix(transformation.rotationScaling())
        .setProjectionMatrix(projection);
}

void PCMoonGlobeApplication::drawEvent()
{
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    setShaderUniforms();
    // shader.setDiffuseColor(Color4::fromHSV(216.0_degf, 0.85f, 1.0f));
    // moon_globe.draw(shader, camera);

    labels.draw(transformation * scaling, projection);

    swapBuffers();
}


void PCMoonGlobeApplication::mousePressEvent(MouseEvent &event)
{
    event.setAccepted();
    redraw();
}

void PCMoonGlobeApplication::mouseReleaseEvent(MouseEvent &event)
{
    transformation = transformation * Matrix4::rotationY(5.0_degf);

    event.setAccepted();
    redraw();
}

void PCMoonGlobeApplication::keyPressEvent(KeyEvent& event)
{
    float scale = 2;
    scale_k += scale - 1.0;
    scale_k = scale_k > (CAMERA_BASE_DISTANCE-0.5f) ? (CAMERA_BASE_DISTANCE-0.5f) : scale_k;
    scale_k = scale_k < 0.5f ? 0.5f : scale_k;
    scaling = Matrix4::scaling({scale_k, scale_k, scale_k});
    Error() << scale_k;
    labels.set_scale(scale_k);
    event.setAccepted();
    redraw();
}

void PCMoonGlobeApplication::mouseMoveEvent(MouseMoveEvent &event)
{
    event.setAccepted();
}
