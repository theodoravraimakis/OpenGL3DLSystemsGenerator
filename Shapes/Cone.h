//
// Created by Theodora Vraimakis on 14/02/2023.
//

#ifndef FINALYEARPROJECT_CONE_H
#define FINALYEARPROJECT_CONE_H

#include "Mesh.h"

class Cone : public Shape {
public:
    Cone(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );
    Cone();
    void make() override;

//    MeshData getMesh();
//    glm::vec3& getColor();
//    void setColor(glm::vec3& newCol);
//    void setCap(bool newCap);
//    MeshData updateColor(glm::vec4 newCol);
//    void updateMesh();
//    void createVAO();
//    void updateVAO();
//    GLuint getVAO();
//    size_t getVertexCount();
//    bool* getCap();
//    bool* changeCap();
//    ~Cone();

protected:
//    Mesh m;
//    MeshData m_coneMesh;
//    glm::vec3 m_color;
//    GLuint m_VAO;
//    bool m_cap;
//    bool m_change;
//    int m_count;
//    glm::mat4 m_transformations;
//float m_diameter;

private:
    friend class UI;
    friend class coordianteAxesArrows;
    friend class Render;
    friend class Turtle;
};


#endif //FINALYEARPROJECT_CONE_H
