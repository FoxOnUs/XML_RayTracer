
#include "raytracing.h"
using namespace std;
void RayTracing::write_color(ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

bool RayTracing::rayTriangleIntersect(
    const vec3 &orig, const vec3 &dir,
    const vec3 v0, const vec3 v1, const vec3 v2,
    float &t)
{
    // compute plane's normal
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;
    // no need to normalize
    vec3 N = cross(v0v1, v0v2); // N
    float area2 = N.length();

    // Step 1: finding P

    // check if ray and plane are parallel ?
    float NdotRayDirection = dot(N, dir);
    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false;                      // they are parallel so they don't intersect !

    // compute d parameter using equation 2
    float d = -dot(N, v0);

    // compute t (equation 3)
    t = -(dot(N, orig) + d) / NdotRayDirection;

    // check if the triangle is in behind the ray
    if (t < 0)
        return false; // the triangle is behind

    // compute the intersection point using equation 1
    vec3 P = orig + t * dir;

    // Step 2: inside-outside test
    vec3 C; // vector perpendicular to triangle's plane

    // edge 0
    vec3 edge0 = v1 - v0;
    vec3 vp0 = P - v0;
    C = cross(edge0, vp0);
    if (dot(N, C) < 0)
        return false; // P is on the right side

    // edge 1
    vec3 edge1 = v2 - v1;
    vec3 vp1 = P - v1;
    C = cross(edge1, vp1);
    if (dot(N, C) < 0)
        return false; // P is on the right side

    // edge 2
    vec3 edge2 = v0 - v2;
    vec3 vp2 = P - v2;
    C = cross(edge2, vp2);
    if (dot(N, C) < 0)
        return false; // P is on the right side;

    return true; // this ray hits the triangle
}
inline double RayTracing::clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}
vec3 RayTracing::normal(const vec3 v0, const vec3 v1, const vec3 v2)
{
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;
    // no need to normalize
    vec3 N = cross(v0v1, v0v2);
    return N;
}

color RayTracing::ray_color(const ray &r)
{
    vector<vec3> temp;

    Mesh tempM;
    vec3 tempFace;
    vec3 unit_direction = unit_vector(r.direction());
    double cosO;
    float t = 0.5 * (unit_direction.y() + 1.0);
    float tmin = max(__FLT_MAX__, t);
    color tempC;
    double distance1;
    int flag = 0;
    for (Mesh i : meshes)
    {
        temp = i.getFaces();

        for (vec3 j : temp)
        {
            if (rayTriangleIntersect(r.origin(), unit_direction, vertexes.at(j.x()), vertexes.at(j.y()),
                                     vertexes.at(j.z()), t))
            {
                if (t < tmin)
                {
                    tempM = i;
                    tempFace = j;
                    flag = 1;
                    tmin = t;
                }
            }
        }
    }

    if (flag != 0)
    {

        tempC = materials[tempM.getMaterialID()].getAmbient() * (ambientLight / 255);
        for (pointlight pl1 : pls)
        {

            vec3 tempPosition = (unit_direction * tmin - r.origin()) - pl1.pointL_pos;
            double distance = sqrt(pow(tempPosition.x(), 2) + pow(tempPosition.y(), 2)) + pow(tempPosition.z(), 2);
            cosO = dot(-unit_direction, normal(vertexes.at(tempFace.x()), vertexes.at(tempFace.y()),
                                               vertexes.at(tempFace.z())));
            //if (shadowHit(tempPosition, pl1.pointL_pos - tempPosition, pl1.pointL_pos))
            //    continue;
            tempC += materials[tempM.getMaterialID()].getDiffuse() * max(0.0, cosO) * (pl1.pointL_int / distance);

            vec3 vech = pl1.pointL_pos - tempPosition + pov.getPosition() - tempPosition;
            vech /= vec3(fabs(vech.x()), fabs(vech.y()), fabs(vech.z()));
            double cosa = dot(normal(vertexes.at(tempFace.x()), vertexes.at(tempFace.y()),
                                     vertexes.at(tempFace.z())),
                              vech);
            cosa = pow(cosa, materials[tempM.getMaterialID()].getPhong());
            tempC += materials[tempM.getMaterialID()].getSpecular() * cosa * (pl1.pointL_int / distance);
        }
        return tempC;
    }
    return background;
}

bool RayTracing::shadowHit(const point3 origin, const vec3 direction, const point3 pLight)
{
    vector<vec3> temp;
    ray r = ray(origin, direction);
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y());
    for (Mesh i : meshes)
    {
        temp = i.getFaces();

        for (vec3 j : temp)
        {

            if (rayTriangleIntersect(r.origin(), unit_direction, vertexes.at(j.x()), vertexes.at(j.y()),
                                     vertexes.at(j.z()), t))
            {
                return true;
            }
        }
    }
    return false;
}

void RayTracing::writeToPPM()
{
    background = color(background.x() / 255, background.y() / 255, background.z() / 255);
    cout << "P3\n"
         << pov.getImx() << " " << pov.getImy() << "\n255\n";
    auto origin = point3(pov.getPosition().x(), pov.getPosition().y(), pov.getPosition().z());
    auto horizontal = vec3(pov.getNearR() - pov.getNearL(), 0, 0);
    auto vertical = vec3(0, pov.getNearT() - pov.getNearB(), 0);
    auto upper_left_corner = origin - horizontal / 2 + vertical / 2 - vec3(0, 0, pov.getNearD());
    for (int j = 0; j < pov.getImy(); ++j)
    {
        for (int i = 0; i < pov.getImx(); ++i)
        {
            auto u = double(i) / (pov.getImx() + 1);
            auto v = double(j) / (pov.getImy() - 1);
            ray r(origin, upper_left_corner + u * horizontal - v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(cout, pixel_color, 1);
        }
    }
}