#include "Fragment/Fragment.h"

Fragment::Fragment(Coords left_bottom, Coords left_top, Coords right_top,
                   Coords right_bottom, TextureId texture_id)
    : texture_id(texture_id)
    , left_bottom(left_bottom)
    , left_top(left_top)
    , right_top(right_top)
    , right_bottom(right_bottom)
{
    generateMesh(left_bottom, left_top, right_top, right_bottom);
    // std:: << "Fragment()_end";
}

void Fragment::generateMesh(Coords left_bottom, Coords left_top, Coords right_top, Coords right_bottom)
{
    Trade::MeshData3D mesh_data = generate_mesh(18, 18, left_bottom, left_top,
                                                right_top,   right_bottom);

    vertex_buffer.setData(MeshTools::interleave(mesh_data.positions(0),
                                                mesh_data.normals(0),
                                                mesh_data.textureCoords2D(0)),
                          BufferUsage::StaticDraw);

    mesh.setPrimitive(Magnum::MeshPrimitive::Triangles)//mesh_data.primitive())
        .setCount(mesh_data.positions(0).size())
        .addVertexBuffer(vertex_buffer, 0,
                         Shaders::Phong::Position{},
                         Shaders::Phong::Normal{},
                         Shaders::Phong::TextureCoordinates{});
}

void Fragment::draw(MyShader& shader)
{
    Moonglobe::ResourceManager& manager = Moonglobe::ResourceManager::instance();
    auto texture = manager.getTexture(texture_id);

    // std::cout << "\n count = " << texture.use_count() << std::endl;

    shader.setDiffuseTexture(*(texture.get()));
    mesh.draw(shader);
}
