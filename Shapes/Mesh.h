//
// Created by Theodora Vraimakis on 12/02/2023.
//

#ifndef FINALYEARPROJECT_MESH_H
#define FINALYEARPROJECT_MESH_H

#define GLFW_INCLUDE_NONE

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


struct MeshData
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec3> normals;
};

class Mesh {
public:
    GLuint createVAO(MeshData const&);
    MeshData concatenate(MeshData aM, MeshData const& aN );
    friend class coordianteAxesArrows;
    inline void clearMesh(MeshData mesh) {
        mesh.colors.clear();
        mesh.normals.clear();
        mesh.positions.clear();
    }
};

class Shape {
public:
    virtual size_t getVertexCount() = 0;
    virtual GLuint getVAO() = 0;
    virtual glm::vec3& getColor() = 0;
    virtual void setColor(glm::vec3& newCol) = 0;
    virtual bool* changeCap() = 0;
    virtual void updateCap(bool newCap) = 0;
    virtual bool* getCap() = 0;
};


#endif //FINALYEARPROJECT_MESH_H
