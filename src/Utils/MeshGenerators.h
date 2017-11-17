#ifndef MESHGENERATORS_H
#define MESHGENERATORS_H


// #include <Corrade/PluginManager/Manager.h>
// #include <Magnum/Buffer.h>
// #include <Magnum/Renderer.h>
// #include <Magnum/DefaultFramebuffer.h>
// #include <Magnum/MeshTools/Interleave.h>
// #include <Magnum/MeshTools/CompressIndices.h>
// #include <Magnum/Platform/Sdl2Application.h>
// #include <Magnum/Primitives/UVSphere.h>
// #include <Magnum/Shaders/Phong.h>
// #include <Magnum/Trade/MeshData3D.h>
// #include <Magnum/Trade/AbstractImporter.h>
// #include <Magnum/Trade/ImageData.h>
#include <Magnum/Texture.h> // Не трогать там реализация Vector3
#include <Magnum/MeshTools/CompressIndices.h> // не трогать, там MeshPrimitive
#include <Magnum/Math/Math.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Magnum.h>
#include "Coords/Coords.h"

void normalize(Magnum::Vector3& vector);

void compute_decart_coord(Coords& coords);

std::vector<Coords> generate_linear_mesh(int columns, Coords left_bottom, Coords left_top,
                                         Coords right_top,   Coords right_bottom);

Magnum::Trade::MeshData3D generate_mesh(int rows, int columns,
                                        Coords left_bottom, Coords left_top,
                                        Coords right_top,   Coords right_bottom);

void print_coord(Coords& coords);
void print_vector(const std::vector<Coords>& v);
void append_vector(std::vector<Coords>& total, std::vector<Coords>& part);

Magnum::Vector2 compute_texture_coords(const Coords& point,   const Coords& left_bottom,
                                       const Coords& left_top,const Coords& right_bottom);


#endif
