#include "material.hpp"

void Material::setId(int input)
{
    id = input;
}
void Material::setAmbient(vec3 imp)
{
    ambient.e[0] = imp.e[0];
    ambient.e[1] = imp.e[1];
    ambient.e[2] = imp.e[2];
}
void Material::setDiffuse(vec3 imp)
{
    diffuse.e[0] = imp.e[0];
    diffuse.e[1] = imp.e[1];
    diffuse.e[2] = imp.e[2];
}
void Material::setSpecular(vec3 imp)
{
    specular.e[0] = imp.e[0];
    specular.e[1] = imp.e[1];
    specular.e[2] = imp.e[2];
}
void Material::setPhong(float phongV)
{
    phong_e = phongV;
}
void Material::setMirror(vec3 imp)
{
    mirror_ref.e[0] = imp.e[0];
    mirror_ref.e[1] = imp.e[1];
    mirror_ref.e[2] = imp.e[2];
}

int Material::getId() { return id; }
vec3 Material::getAmbient() { return ambient; }
vec3 Material::getDiffuse() { return diffuse; }
vec3 Material::getSpecular() { return specular; }
float Material::getPhong() { return phong_e; }
vec3 Material::getMirror() { return mirror_ref; }

Material::~Material()
{
    return;
}
Material::Material()
{
    id = 0;
}