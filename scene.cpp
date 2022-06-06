#include "raytracing.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

color getColor(string input);
vec3 getVec3(string input);

int main(void)
{
    XMLDocument doc;
    doc.LoadFile("input.xml");

    RayTracing scene;

    XMLElement *pRootElement = doc.RootElement();

    const char *tmp = pRootElement->FirstChildElement("maxraytracedepth")->GetText();

    scene.raytracedepth = stoi(tmp);

    tmp = pRootElement->FirstChildElement("background")->GetText();

    scene.background = getColor(tmp);

    /**Start of camera*/
    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("position")->GetText();

    vec3 position = getVec3(tmp);

    scene.pov.setPosition(position.x(), position.y(), position.z());
    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("gaze")->GetText();
    position = getVec3(tmp);
    scene.pov.setGaze(position.x(), position.y(), position.z());
    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("up")->GetText();
    position = getVec3(tmp);
    scene.pov.setUp(position.x(), position.y(), position.z());

    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("nearplane")->GetText();
    double temp1, temp2, temp3, temp4;
    sscanf(tmp, "%lf %lf %lf %lf", &temp1, &temp2, &temp3, &temp4);
    scene.pov.setNearL(temp1);
    scene.pov.setNearR(temp2);
    scene.pov.setNearB(temp3);
    scene.pov.setNearT(temp4);
    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("neardistance")->GetText();
    scene.pov.setNearD(stod(tmp));
    tmp = pRootElement->FirstChildElement("camera")->FirstChildElement("imageresolution")->GetText();
    sscanf(tmp, "%lf %lf", &temp1, &temp2);
    scene.pov.setImx(temp1);
    scene.pov.setImy(temp2);

    /**End of camera*/

    // lights
    tmp = pRootElement->FirstChildElement("lights")->FirstChildElement("ambientlight")->GetText();
    scene.ambientLight = getVec3(tmp);
    pointlight tempPL;
    for (XMLElement *e = pRootElement->FirstChildElement("lights")->FirstChildElement("pointlight"); e != NULL; e = e->NextSiblingElement("pointlight"))
    {
        tmp = e->Attribute("id");
        tempPL.id = stoi(tmp);
        tmp = e->FirstChildElement("position")->GetText();
        tempPL.pointL_pos = getVec3(tmp);
        tmp = e->FirstChildElement("intensity")->GetText();
        tempPL.pointL_int = getVec3(tmp);
        scene.pls.push_back(tempPL);
    }
    // Materials
    Material tempM;
    int tempMid;
    vec3 tempCoord;
    for (XMLElement *e = pRootElement->FirstChildElement("materials")->FirstChildElement("material"); e != NULL; e = e->NextSiblingElement("material"))
    {
        tmp = e->Attribute("id");
        tempM.setId(stoi(tmp));
        tempMid = tempM.getId();
        tmp = e->FirstChildElement("ambient")->GetText();
        tempM.setAmbient(getVec3(tmp));
        tmp = e->FirstChildElement("diffuse")->GetText();
        tempM.setDiffuse(getVec3(tmp));
        tmp = e->FirstChildElement("specular")->GetText();
        tempM.setSpecular(getVec3(tmp));
        tmp = e->FirstChildElement("phongexponent")->GetText();
        tempM.setPhong(stod(tmp));
        tmp = e->FirstChildElement("mirrorreflectance")->GetText();
        tempM.setMirror(getVec3(tmp));
        scene.materials[tempMid] = tempM;
    }

    // Vertexes
    tmp = pRootElement->FirstChildElement("vertexdata")->GetText();
    string pch;
    pch.append(tmp);
    string delim = "\n";
    size_t pos = 0;
    for (int i = 0; (pos = pch.find(delim)) != string::npos; i++)
    {
        tempCoord = getVec3(pch.substr(0, pos));
        scene.vertexes[i] = tempCoord;
        pch.erase(0, pos + delim.length());
    }
    // MESHES
    pch.clear();
    Mesh tempMesh;
    for (XMLElement *e = pRootElement->FirstChildElement("objects")->FirstChildElement("mesh"); e != NULL; e = e->NextSiblingElement("mesh"))
    {
        tmp = e->Attribute("id");
        tempMesh.setID(stoi(tmp));
        tmp = e->FirstChildElement("materialid")->GetText();
        tempMesh.setMaterialID(stoi(tmp));
        tmp = e->FirstChildElement("faces")->GetText();

        pch.append(tmp);
        size_t pos = 0;
        for (int i = 0; (pos = pch.find(delim)) != string::npos; i++)
        {
            tempCoord = getVec3(pch.substr(0, pos));
            tempMesh.addFace(tempCoord);
            pch.erase(0, pos + delim.length());
        }
        scene.meshes.push_back(tempMesh);
    }

    scene.writeToPPM();

    std::cerr << "\nDone.\n";

    return 0;
}

color getColor(string input)
{
    color temp;
    sscanf(input.c_str(), "%lf %lf %lf", &temp.e[0], &temp.e[1], &temp.e[2]);
    return temp;
}
vec3 getVec3(string input)
{
    vec3 temp;
    sscanf(input.c_str(), "%lf %lf %lf", &temp.e[0], &temp.e[1], &temp.e[2]);
    return temp;
}
