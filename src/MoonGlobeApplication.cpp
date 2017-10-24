#include "MoonGlobeApplication.h"

using namespace Magnum;

MoonGlobeApplication::MoonGlobeApplication(const Arguments &arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("sphere")}
    , shader{Shaders::Phong::Flag::DiffuseTexture}
    , camera(0, 0, -10)
{
    //enable depthtest and faceculling
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);
    initProjectionMatrix();
}

void MoonGlobeApplication::initProjectionMatrix()
{
    // set transform matrix
    transformation = Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
    // set perspective projection
    projection = Matrix4::perspectiveProjection(
        35.0_degf,
        Vector2{defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)
        * Matrix4::translation(Vector3::zAxis(camera.z));
}

void MoonGlobeApplication::setShaderUniforms()
{
    // set shaders uniforms
    shader.setLightPosition({0.0f,1.0f, 5.0f})
        // .setDiffuseTexture(texture)
        .setLightColor(Color3{1.0f, 1.0f, 1.0f})
        .setTransformationMatrix(transformation)
        .setNormalMatrix(transformation.rotationScaling())
        .setProjectionMatrix(projection);
}

void MoonGlobeApplication::drawEvent()
{
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);


    setShaderUniforms();
    // shader.setDiffuseColor(Color4::fromHSV(216.0_degf, 0.85f, 1.0f));
    moon_globe.draw(shader, camera);

    swapBuffers();
}

// void MoonGlobeApplication::drawEvent()
// {
//     defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);
//     Coords l_t = {0,         0};
//     Coords l_b = {M_PI / 2,  0};
//     Coords r_t = {0,         M_PI / 2};
//     Coords r_b = {M_PI / 2,  M_PI / 2};
//     std::cout << "\n";
//     static Fragment f(l_b, l_t, r_t, r_b, "0");
//     std::cout << "\nFINISH\n" << M_PI;
//
//     setShaderUniforms();
//     // shader.setDiffuseColor(Color4::fromHSV(216.0_degf, 0.85f, 1.0f));
//
//     f.draw(shader);
//     swapBuffers();
// }

void MoonGlobeApplication::mousePressEvent(MouseEvent &event)
{
    if (event.button() != MouseEvent::Button::Left)
        return;

    previousMousePosition = event.position();
    event.setAccepted();
}

void MoonGlobeApplication::mouseReleaseEvent(MouseEvent &event)
{
    event.setAccepted();
    redraw();
}

void MoonGlobeApplication::mouseMoveEvent(MouseMoveEvent &event)
{
    if (!(event.buttons() & MouseMoveEvent::Button::Left))
        return;
    const Vector2 delta = 3.0f *
        Vector2{event.position() - previousMousePosition} /
        Vector2{defaultFramebuffer.viewport().size()};

    transformation = Matrix4::rotationX(Rad{delta.y()}) *
        transformation *
        Matrix4::rotationY(Rad{delta.x()});

    previousMousePosition = event.position();
    event.setAccepted();
    redraw();
}
