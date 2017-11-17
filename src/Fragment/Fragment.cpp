#include "Fragment/Fragment.h"

Fragment::Fragment(Coords left_bottom, Coords left_top, Coords right_top,
                   Coords right_bottom, TextureId texture_id)
    : texture_id(texture_id)
    , left_bottom(left_bottom)
    , left_top(left_top)
    , right_top(right_top)
    , right_bottom(right_bottom)
{
    print_coord(left_bottom);
    generateMesh(left_bottom, left_top, right_top, right_bottom);
    // std:: << "Fragment()_end";
}

void Fragment::generateMesh(Coords left_bottom, Coords left_top, Coords right_top, Coords right_bottom)
{
    Trade::MeshData3D mesh_data = generate_mesh(18, 18, left_bottom, left_top,
                                                right_top,   right_bottom);

    vertex_buffer.setData(MeshTools::interleave(mesh_data.positions(0),
                                                mesh_data.normals(0)),
                                                // mesh_data.textureCoords2D(0)),
                          BufferUsage::StaticDraw);

    mesh.setPrimitive(Magnum::MeshPrimitive::Triangles)//mesh_data.primitive())
        .setCount(mesh_data.positions(0).size())
        .addVertexBuffer(vertex_buffer, 0,
                         Shaders::Phong::Position{},
                         Shaders::Phong::Normal{});//,
                        //  Shaders::Phong::TextureCoordinates{});
}

void Fragment::loadTexture()
{
    Moonglobe::ResourceManager& manager = Moonglobe::ResourceManager::instance();
    texture = manager.getTexture(texture_id);
}

void Fragment::draw(MyShader& shader)
{
    if (!texture) {
        loadTexture();
    }
    // std::cout << "\n count = " << texture.use_count() << std::endl;

    shader.setDiffuseTexture(*(texture.get()));
    mesh.draw(shader);
}

Magnum::Vector3 from_point_to_camera(const Coords& point, const Camera& camera)
{
    return Vector3(point.x - camera.x, point.y - camera.y, point.z - camera.z);
}

Magnum::Vector3 from_point_to_center(const Coords& point)
{
    return Vector3(-point.x, -point.y, -point.z);
}


bool isVisiblePoint(const Coords& coord, const Camera& camera)
{
    Magnum::Vector3 to_camera = from_point_to_camera(coord, camera);
    Magnum::Vector3 to_center = from_point_to_center(coord);

    to_camera = to_camera.normalized();
    to_center = to_center.normalized();

    Magnum::Math::Rad<float> angle = Magnum::Math::angle(to_camera, to_center);

    Magnum::Math::Deg<float> angle_deg = Magnum::Math::Deg<float>(angle);

    Magnum::Debug() << angle << " \n";
    Magnum::Debug() << angle_deg << " \n";
    if (angle_deg < 90.0_degf) {
        return false;
    } else {
        return true;
    }
}

bool Fragment::isVisible(const Camera& camera)
{
    if (!isVisiblePoint(left_bottom,  camera) &&
        !isVisiblePoint(right_bottom, camera) &&
        !isVisiblePoint(right_top, camera) &&
        !isVisiblePoint(left_top,  camera)
    ) {
        return false;
    }
    return true;
}

Fragment::~Fragment()
{
    mesh.release();
    vertex_buffer.release();
}
