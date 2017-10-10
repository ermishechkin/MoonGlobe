#include "moonglobe.h"

using namespace Magnum;

MoonGlobe::MoonGlobe(const Arguments &arguments)
    : Platform::Application{arguments, Configuration{}.setTitle("sphere")}
    , shader{Shaders::Phong::Flag::DiffuseTexture}
{
    //enable depthtest and faceculling
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);
    initProjectionMatrix();

    createMesh();
    loadTexture();
}

void MoonGlobe::loadTexture()
{
    // load texture
    PluginManager::Manager<Trade::AbstractImporter> manager{MAGNUM_PLUGINS_IMPORTER_DIR};
    std::unique_ptr<Trade::AbstractImporter> importer = manager.loadAndInstantiate("JpegImporter");
    if (!importer) {
        Error() << "Cannot load importer plugin from" << manager.pluginDirectory();
        std::exit(1);
    }

    const Utility::Resource rs{"sphere-data"};
    if(!importer->openData(rs.getRaw("moon.jpg")))
        std::exit(2);

    std::optional<Trade::ImageData2D> image = importer->image2D(0);
    CORRADE_INTERNAL_ASSERT(image);

    // set texture params
    texture.setWrapping(Sampler::Wrapping::MirroredRepeat)
        .setMagnificationFilter(Sampler::Filter::Linear)
        .setMinificationFilter(Sampler::Filter::Linear)
        .setStorage(1, TextureFormat::R8, image->size())
        .setSubImage(0, {}, *image);
}

void MoonGlobe::initProjectionMatrix()
{
    // set transform matrix
    transformation = Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
    color = Color3::fromHsv(35.0_degf, 1.0f, 1.0f);

    // set perspective projection
    projection = Matrix4::perspectiveProjection(
        35.0_degf,
        Vector2{defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)
        * Matrix4::translation(Vector3::zAxis(-10.0f));
}

void MoonGlobe::createMesh()
{
    // create sphere mesh
    const Trade::MeshData3D sphere =
        Primitives::UVSphere::solid(32, 32, Primitives::UVSphere::TextureCoords::Generate);

    vertexBuffer.setData(MeshTools::interleave(sphere.positions(0),
                                               sphere.normals(0),
                                               sphere.textureCoords2D(0)),
                         BufferUsage::StaticDraw);

    Containers::Array<char> indexData;
    Mesh::IndexType indexType;
    UnsignedInt indexStart, indexEnd;

    // feel index buffer
    std::tie(indexData, indexType,
             indexStart, indexEnd) = MeshTools::compressIndices(sphere.indices());
    indexBuffer.setData(indexData, BufferUsage::StaticDraw);

//     configure mesh params
    mesh.setPrimitive(sphere.primitive())
        .setCount(sphere.indices().size())
        .addVertexBuffer(vertexBuffer, 0, Shaders::Phong::Position{},
                         Shaders::Phong::Normal{},
                         Shaders::Phong::TextureCoordinates{})
        .setIndexBuffer(indexBuffer, 0, indexType, indexStart, indexEnd);
}

void MoonGlobe::setShaderUniforms()
{
    // set shaders uniforms
    shader.setLightPosition({0.0f,1.0f, 5.0f})
        .setDiffuseTexture(texture)
        .setLightColor(Color3{1.0f, 1.0f, 1.0f})
        .setTransformationMatrix(transformation)
        .setNormalMatrix(transformation.rotationScaling())
        .setProjectionMatrix(projection);
}

void MoonGlobe::drawEvent()
{
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);
    setShaderUniforms();
    mesh.draw(shader);
    swapBuffers();
}

void MoonGlobe::mousePressEvent(MouseEvent &event)
{
    if (event.button() != MouseEvent::Button::Left)
        return;

    previousMousePosition = event.position();
    event.setAccepted();
}

void MoonGlobe::mouseReleaseEvent(MouseEvent &event)
{
    color = Color3::fromHsv(color.hue() + 50.0_degf, 1.0f, 1.0f);

    event.setAccepted();
    redraw();
}

void MoonGlobe::mouseMoveEvent(MouseMoveEvent &event)
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

