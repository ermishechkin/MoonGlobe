#ifndef COORDS_H
#define COORDS_H

struct Coords_temp
{
    float x = 0;
    float y = 0;
    float z = 0;
    float theta = 0;
    float phi = 0;

    Coords_temp() = default;
    Coords_temp(const Coords_temp&) = default;


    Coords_temp(float theta_, float phi_)
    {
        theta = theta_;
        phi = phi_;
    }
};

typedef Coords_temp Coords;

#endif
