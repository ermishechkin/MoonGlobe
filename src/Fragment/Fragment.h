#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <iostream>
#include <utility>
#include <string>
#include <vector>


#include <Magnum/Buffer.h>
#include <Magnum/Magnum.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Texture.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/MeshTools/Interleave.h>

#include "Coords/Coords.h"
#include "Utils/MeshGenerators.h"
#include "ResourceManager/ResourceManager.h"

using namespace Magnum;

typedef Shaders::Phong MyShader;

class Fragment
{
public:
    Fragment(Coords left_bottom, Coords left_top, Coords right_top, Coords right_bottom, TextureId texture_id);
    void draw(MyShader& shader);

    void generateMesh(Coords left_bottom, Coords left_top, Coords right_top, Coords right_bottom);
    void loadTexture();

    Fragment() = delete;
    Fragment(const Fragment&) = delete;
    Fragment operator = (const Fragment&) = delete;


private:
    TextureId texture_id;
    Mesh mesh;
    Buffer vertex_buffer;


    Coords left_bottom;
    Coords left_top;
    Coords right_top;
    Coords right_bottom;
};

#endif
