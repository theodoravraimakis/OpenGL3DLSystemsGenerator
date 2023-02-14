//
// Created by Theodora Vraimakis on 12/02/2023.
//

#ifndef FINALYEARPROJECT_CYLINDER_H
#define FINALYEARPROJECT_CYLINDER_H

#include "Mesh.h"
//#include "../Config/Config.h"

constexpr float kPi_ = 3.1415926f;

class Cylinder : public Shape {
public:
    Cylinder(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );
    void makeCylinder(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );

    MeshData getMesh();
    glm::vec3& getColor();
    void setColor(glm::vec3& newCol);
    void updateCap(bool newCap);
    MeshData updateColor(glm::vec4 newCol);
    void updateMesh();
    void createVAO();
    void updateVAO();
    GLuint getVAO();
    size_t getVertexCount();
    bool* getCap();
    bool* changeCap();
    ~Cylinder();

protected:
    Mesh m;
    MeshData m_cylinderMesh;
    glm::vec3 m_color;
    GLuint m_VAO;
    bool m_cap;
    bool m_change;
    int m_count;
    glm::mat4 m_transformations;

private:
    friend class UI;
    friend class coordianteAxesArrows;
    friend class Render;
    friend class Turtle;
};


#endif //FINALYEARPROJECT_CYLINDER_H
