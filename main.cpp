//
// Created by Theodora Vraimakis on 11/02/2023.
//
#include "Render/Render.h"
//#include "iostream"

//#include "Cylinder/Mesh.h"
//using namespace std;
//
//struct Vec3f {
//    float x, y, z;
//};
//struct Vec4f {
//    float x, y, z, a;
//};
//struct SimpleMeshData
//{
//    std::vector<Vec3f> positions;
//    std::vector<Vec4f> colors;
//    std::vector<Vec3f> normals;
//};
//struct MeshData
//{
//    glm::vec3 positions;
//    glm::vec3 colors;
//    glm::vec3 normals;
//};


int main() {
    Render renderer;
//    MeshData rootCylinder = Cylinder::makeCylinder(true, 128, {0.48f, 0.33f, 0.25f }, glm::mat4());
//    size_t vertexCountRootCylinder = rootCylinder.positions.size();
//    std::cout << vertexCountRootCylinder <<endl
//    << sizeof(rootCylinder.positions);

    renderer.run();
//    glm::vec3 v(0.0f, 1.0f, 12.0f);
//    MeshData MD2 = {{v}, {glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)}, {v}};
//    auto v2 = Vec3f{0.0f, 1.0f, 12.0f};
//    auto v3 = Vec4f{0.0f, 1.0f, 12.0f, 0.0f};
//    SimpleMeshData MD = SimpleMeshData{{v2, v2, v2, v2, v2}, {v3, v3}, {v2} };
//    cout <<" sizeof(glm::vec3)" << sizeof(glm::vec3) << endl << glm::length(glm::vec3()) << endl << glm::vec3::length() << endl
//    << MD2.positions.data() << endl
//     ;
////
//    cout << "sizeof(Vec3f)" << sizeof(Vec3f) << endl << MD.positions.size() << endl << MD.positions.data() << endl;
//
//    std::vector<glm::vec3> v4 = {v, v, v};
//    cout << v4.size();

    return 0;
}