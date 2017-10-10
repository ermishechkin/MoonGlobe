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
#include <src/Magnum/PixelFormat.h>
#include "configure.h"

namespace Magnum {

using namespace Magnum::Math::Literals;

class MoonGlobe : public Platform::Application {
 public:
    explicit MoonGlobe(const Arguments &arguments);

 private:
    void drawEvent() override;
    void mousePressEvent(MouseEvent &event) override;
    void mouseReleaseEvent(MouseEvent &event) override;
    void mouseMoveEvent(MouseMoveEvent &event) override;

    void createMesh();
    void loadTexture();
    void initProjectionMatrix();
    void setShaderUniforms();


    Buffer indexBuffer, vertexBuffer;
    Mesh mesh;
    Shaders::Phong shader;

    Matrix4 transformation, projection;
    Vector2i previousMousePosition;
    Color3 color;
    Texture2D texture;
};

} // end of namespace
