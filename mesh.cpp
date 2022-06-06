#include "mesh.hpp"

void Mesh::setMaterial(Material input)
{
    mat = input;
}
void Mesh::setID(int idi)
{
    id = idi;
}
void Mesh::setMaterialID(int input)
{
    materialId = input;
}
void Mesh::addFace(vec3 input)
{
    faces.push_back(input);
}

Material Mesh::getMaterial()
{
    return mat;
}
int Mesh::getID() { return id; }
int Mesh::getMaterialID() { return materialId; }
vector<vec3> Mesh::getFaces()
{
    return faces;
}
Mesh::~Mesh()
{
    return;
}
Mesh::Mesh()
{
    id = 0;
}