#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "vec3.h"

class camera
{
private:
    vec3 position;
    vec3 gaze;
    vec3 up;
    double image_res_x;
    double image_res_y;
    double nearp_t, nearp_l, nearp_r, nearp_b;
    double neard;

public:
    camera(/* args */);
    ~camera();
    void setPosition(double xi, double yi, double zi);
    void setGaze(double xi, double yi, double zi);
    void setUp(double xi, double yi, double zi);
    void setImx(double input);
    void setImy(double input);
    void setNearT(double input);
    void setNearL(double input);
    void setNearR(double input);
    void setNearB(double input);
    void setNearD(double input);

    vec3 getPosition();
    vec3 getGaze();
    vec3 getUp();
    double getImx();
    double getImy();
    double getNearT();
    double getNearL();
    double getNearR();
    double getNearB();
    double getNearD();
};

#endif