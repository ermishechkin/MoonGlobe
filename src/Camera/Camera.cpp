#include "Camera/Camera.h"

Camera::Camera(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{}

void Camera::scale(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
}
