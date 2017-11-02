#ifndef PC_MOON_GLOBE_APPLICATION_H
#define PC_MOON_GLOBE_APPLICATION_H

// #include "Fragment/Fragment.h"
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/UVSphere.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Texture.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/PixelFormat.h>

#include "MoonGlobe/MoonGlobe.h"
#include "Camera/Camera.h"
#include "LabelManager/LabelManager.h"

namespace Magnum {

using namespace Magnum::Math::Literals;

class PCMoonGlobeApplication : public Platform::Application {
 public:
    explicit PCMoonGlobeApplication(const Arguments &arguments);

 private:
    void drawEvent() override;
    void mousePressEvent(MouseEvent &event) override;
    void mouseReleaseEvent(MouseEvent &event) override;
    void mouseMoveEvent(MouseMoveEvent &event) override;
    void initProjectionMatrix();
    void setShaderUniforms();


    LabelManager labels;
    MoonGlobe moon_globe;
    Shaders::Phong shader;
    Camera camera;

    Matrix4 transformation, projection;
    Vector2i previousMousePosition;
};

} // end of namespace

#endif
