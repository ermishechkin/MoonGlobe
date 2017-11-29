#ifndef MOON_GLOBE_APPLICATION_H
#define MOON_GLOBE_APPLICATION_H

// #include "Fragment/Fragment.h"
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Platform/WindowlessEglApplication.h>
#include <Magnum/Primitives/UVSphere.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Texture.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Platform/Context.h>

#include "LabelManager/LabelManager.h"
#include "MoonGlobe/MoonGlobe.h"
#include "Camera/Camera.h"

using namespace Magnum::Math::Literals;

class MoonGlobeApplication {
 public:
    MoonGlobeApplication();
    void drawEvent();
    void rotateEvent(float dx, float dy);
    void rotateEvent2(float x1, float y1, float x2, float y2);
    void zoomEvent(float scale);

 private:
    void initProjectionMatrix();
    void setShaderUniforms();


    Magnum::Platform::Context context;
    Camera camera;
    MoonGlobe moon_globe;
    LabelManager labels;
    Shaders::Phong shader;

    Matrix4 transformation, projection, scaling;
    float scale_k;
};

#endif
