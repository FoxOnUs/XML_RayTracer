#include "camera.hpp"

void camera::setPosition(double xi, double yi, double zi)
{
    position = vec3(xi, yi, zi);
}
void camera::setGaze(double xi, double yi, double zi)
{
    gaze = vec3(xi, yi, zi);
}
void camera::setUp(double xi, double yi, double zi)
{
    up = vec3(xi, yi, zi);
}
void camera::setImx(double input)
{
    image_res_x = input;
}
void camera::setImy(double input)
{
    image_res_y = input;
}
void camera::setNearT(double input)
{
    nearp_t = input;
}
void camera::setNearL(double input)
{
    nearp_l = input;
}
void camera::setNearR(double input)
{
    nearp_r = input;
}
void camera::setNearB(double input)
{
    nearp_b = input;
}
void camera::setNearD(double input)
{
    neard = input;
}

vec3 camera::getPosition() { return position; }
vec3 camera::getGaze() { return gaze; }
vec3 camera::getUp() { return up; }
double camera::getImx() { return image_res_x; }
double camera::getImy() { return image_res_y; }
double camera::getNearT() { return nearp_t; }
double camera::getNearL() { return nearp_l; }
double camera::getNearR() { return nearp_r; }
double camera::getNearB() { return nearp_b; }
double camera::getNearD() { return neard; }
camera::~camera()
{
    return;
}
camera::camera()
{
    neard = 0;
}