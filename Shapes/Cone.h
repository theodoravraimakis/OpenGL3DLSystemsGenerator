//
// Created by Theodora Vraimakis on 14/02/2023.
//

#ifndef FINALYEARPROJECT_CONE_H
#define FINALYEARPROJECT_CONE_H

#include "Mesh.h"

class Cone {
public:
    Cone(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
            );
    void makeCone(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
    );

    MeshData getMesh();
    glm::vec3 getColor();
    void setColor(glm::vec3 newCol);
    void updateCap();
    MeshData updateColor(glm::vec4 newCol);
    void updateMesh();
    void createVAO();
    void updateVAO();
    GLuint returnVAO();
    size_t getVertexCount();
    bool getCap() const;
    ~Cone();

protected:
    MeshData m_coneMesh;
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
};


#endif //FINALYEARPROJECT_CONE_H
