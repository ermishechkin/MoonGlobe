#include "MeshGenerators.h"

void normalize(Magnum::Vector3& v)
{
    float l = sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
    v.x() /= l;
    v.y() /= l;
    v.z() /= l;
}


void print_coord(Coords& c)
{
    std:: cout << c.x << " " << c.y << " " << c.z << "\n";
    // std::cout << coords.theta << " " << coords.phi << "\n";
}

/*
    generateMesh - геренериует сетку для одной горизонтальной полосы,
    состоящей из 2 рядов точек в нужном порядке, кладет в массив треугольниками
*/
std::vector<Coords> generate_linear_mesh(int columns, Coords left_bottom, Coords left_top, Coords right_top, Coords right_bottom)
{
    std::vector<Coords> mesh = {};

    // шаг по углу фи
    float delta_phi = (right_bottom.phi - left_bottom.phi) / columns;
    for (int i = 0; i < columns; i++) {
        float phi = left_bottom.phi + delta_phi * i;
        Coords l_b = {left_bottom.theta,  phi};             // left_bottom
        Coords l_t = {left_top.theta,     phi};                // left_top
        Coords r_t = {right_top.theta,    phi + delta_phi};   // right_top
        Coords r_b = {right_bottom.theta, phi + delta_phi};// right_bottom
        // первый треугольник
        mesh.push_back(l_b);
        mesh.push_back(l_t);
        mesh.push_back(r_t);
        // второй треугольник
        mesh.push_back(l_b);
        mesh.push_back(r_t);
        mesh.push_back(r_b);
    }
    return mesh;
}

void append_vector(std::vector<Coords>& total, std::vector<Coords>& part)
{
    for (auto elem: part)
        total.push_back(elem);
}

void print_vector(const std::vector<Coords>& v)
{
    for (const Coords& e: v) {
        // std::cout << e.x << " " << e.y << " " << e.z << " ";
        std::cout << e.theta << " " << e.phi << "\n";
    }
}

// знаю координаты тета, фи и центр с радиусом заполняет декартовы координаты
void compute_decart_coord(Coords& coords)
{
    // const static float center_x = 0;
    // const static float center_y = 0;
    // const static float center_z = 0;
    // float R = 1.0;

    // 0, 0, 0, R = 1
    coords.y = cos(coords.theta);
    coords.x = sin(coords.theta)  * cos(coords.phi);
    coords.z = sin(coords.theta) * sin(coords.phi);
}

Magnum::Vector2 compute_texture_coords(const Coords& point,   const Coords& left_bottom,
                                       const Coords& left_top,const Coords& right_bottom)
{
    float delta_theta = left_bottom.theta - left_top.theta; // > 0
    float delta_phi   = right_bottom.phi - left_bottom.phi; // > 0

    // перевернутые theta
    // M_PI - t - (M_PI - t2) = t2 - t;
    // поэтому для y считаем иначе
    // текстурные координаты - нормированные тета(y) и пси(x)
    float x = (point.phi - left_bottom.phi) / delta_phi;
    float y = (left_bottom.theta - point.theta) / delta_theta;

    // в исходниках картинки есть рамка 14х14 пикселей вокруг нужной части
    // сама картинка 1024х1024

    y = y * (1024.0 - 28.0) / 1024.0;
    x = x * (1024.0 - 28.0) / 1024.0;
    x += 14.0 / 1024.0;
    y += 14.0 / 1024.0;

    return Magnum::Vector2(x, y);
}

// generateMesh - генерирует k горизонтальных полос
Magnum::Trade::MeshData3D generate_mesh(int rows, int columns,
                                        Coords left_bottom, Coords left_top,
                                        Coords right_top, Coords right_bottom)
{
    float delta_theta = (left_bottom.theta - left_top.theta) / rows;
    std::vector<Coords> mesh_total = {};



    Coords l_b = {left_top.theta + delta_theta, left_top.phi};
    Coords l_t = left_top;
    Coords r_t = right_top;
    Coords r_b = {right_top.theta + delta_theta, right_top.phi};

    for (int i = 0; i < rows; i++) {
        std::vector<Coords> mesh_part = generate_linear_mesh(columns, l_b, l_t, r_t, r_b);
        append_vector(mesh_total, mesh_part);

        l_b.theta += delta_theta;
        l_t.theta += delta_theta;
        r_t.theta += delta_theta;
        r_b.theta += delta_theta;
    }

    for (Coords& coords: mesh_total) {
        compute_decart_coord(coords);
    }

    // print_vector(mesh_total);

    std::vector<Magnum::Vector3> positions;
    std::vector<Magnum::Vector3> normals;
    std::vector<Magnum::Vector2> texture_coords;
    for (const Coords& coord: mesh_total) {
        positions.push_back(Magnum::Vector3(coord.x, coord.y, coord.z));
        normals.push_back(Magnum::Vector3(coord.x, coord.y, coord.z));
        texture_coords.push_back(compute_texture_coords(coord, left_bottom,
                                                        left_top, right_bottom));
    }

    Magnum::Trade::MeshData3D mesh(Magnum::MeshPrimitive::Points, // bleat
                                   std::vector<std::uint32_t>(0),
                                   {positions},
                                   {normals},
                                   {texture_coords},
                                   nullptr
    );

    return mesh;
}
