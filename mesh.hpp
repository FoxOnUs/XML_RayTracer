#ifndef MESH_HPP
#define MESH_HPP
#include "material.hpp"
#include <vector>
using namespace std;
class Mesh
{
private:
    Material mat;
    int id;
    int materialId;
    vector<vec3> faces;

public:
    Mesh(/* args */);
    ~Mesh();
    void setMaterial(Material input);
    void setID(int idi);
    void setMaterialID(int input);
    void addFace(vec3 input);

    Material getMaterial();
    int getID();
    int getMaterialID();
    vector<vec3> getFaces();
};

#endif