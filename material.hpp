#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "vec3.h"
#include <string>
using namespace std;
class Material
{
private:
    int id;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float phong_e;
    vec3 mirror_ref;

public:
    Material(/* args */);
    ~Material();
    void setId(int input);
    void setAmbient(vec3);
    void setDiffuse(vec3);
    void setSpecular(vec3);
    void setPhong(float phongV);
    void setMirror(vec3);

    int getId();
    vec3 getAmbient();
    vec3 getDiffuse();
    vec3 getSpecular();
    float getPhong();
    vec3 getMirror();
};

#endif