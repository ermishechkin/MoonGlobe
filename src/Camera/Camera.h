#ifndef CAMERA_H
#define CAMERA_H


struct Camera
{
    Camera(float x, float y, float z);

    void scale(float scale_coefficient);

    float x;
    float y;
    float z;
};


#endif
