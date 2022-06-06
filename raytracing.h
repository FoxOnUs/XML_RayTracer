#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "camera.hpp"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include <map>
#include "mesh.hpp"

class RayTracing
{
public:
    void write_color(ostream &out, color pixel_color, int samples_per_pixel);
    bool rayTriangleIntersect(
        const vec3 &orig, const vec3 &dir,
        const vec3 v0, const vec3 v1, const vec3 v2,
        float &t);

    color ray_color(const ray &r);
    // color ray_color(const ray& r);
    inline double clamp(double x, double min, double max);
    const float kEpsilon = 1e-8;
    camera pov;
    vec3 ambientLight;
    vector<pointlight> pls;
    map<int, Material> materials;
    map<int, vec3> vertexes;
    vector<Mesh> meshes;
    int raytracedepth;
    color background;
    vec3 normal(const vec3 v0, const vec3 v1, const vec3 v2);
    void writeToPPM();
    bool shadowHit(const point3 origin, const vec3 direction, const point3 pLight);
};

#endif