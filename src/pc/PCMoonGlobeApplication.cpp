#include "PCMoonGlobeApplication.h"

using namespace Magnum;

PCMoonGlobeApplication::PCMoonGlobeApplication(const Arguments &arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("sphere")}
    , shader{}//{Shaders::Phong::Flag::DiffuseTexture}
    , camera(0, 0, -5)
{
    //enable depthtest and faceculling
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);
    initProjectionMatrix();
    std::cout << "end PCMoonGlobeApplication()\n";
}

void PCMoonGlobeApplication::initProjectionMatrix()
{
    // set transform matrix
    transformation = Matrix4::rotationX(45.0_degf) * Matrix4::rotationY(40.0_degf);
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
        .setTransformationMatrix(transformation)
        .setNormalMatrix(transformation.rotationScaling())
        .setProjectionMatrix(projection);
}

void PCMoonGlobeApplication::drawEvent()
{
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    // setShaderUniforms();
    // shader.setDiffuseColor(Color4::fromHSV(216.0_degf, 0.85f, 1.0f));
    // moon_globe.draw(shader, camera);

    labels.draw(transformation, projection);

    swapBuffers();
}


void PCMoonGlobeApplication::mousePressEvent(MouseEvent &event)
{
    event.setAccepted();
    redraw();
}

void PCMoonGlobeApplication::mouseReleaseEvent(MouseEvent &event)
{
    event.setAccepted();
}

void PCMoonGlobeApplication::mouseMoveEvent(MouseMoveEvent &event)
{
    event.setAccepted();
}
