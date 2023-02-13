//
// Created by Theodora Vraimakis on 12/02/2023.
//

#ifndef FINALYEARPROJECT_CYLINDER_H
#define FINALYEARPROJECT_CYLINDER_H

#include "glm/glm.hpp"
#include "Mesh.h"

constexpr float kPi_ = 3.1415926f;

class Cylinder {
public:
    Cylinder(
//            bool cap,
//            int count,
//            glm::vec3 color,
//            glm::mat4 transformations
            );
    void makeCylinder(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );
    MeshData getMesh();
    glm::vec3 getColor();
    void setColor(glm::vec3 newCol);
    MeshData updateColor(glm::vec4 newCol);
    void createVAO();
    void updateVAO(MeshData mesh);
    GLuint returnVAO();
    size_t returnVertexCount();
//    void updateColor();
    ~Cylinder();

protected:
    MeshData m_mesh;
    glm::vec3 m_color;
    GLuint m_VAO;
//    static std::vector<glm::vec3> vertices;
//    std::vector<glm::vec4> colors;
//    static std::vector<glm::vec3> normals;
private:
    friend class UI;
};


#endif //FINALYEARPROJECT_CYLINDER_H
