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
    static GLuint createVAO(MeshData const&);
    static MeshData concatenate(MeshData aM, MeshData const& aN );
    friend class coordianteAxesArrows;
    inline static void clearMesh(MeshData mesh) {
        mesh.colors.clear();
        mesh.normals.clear();
        mesh.positions.clear();
    }
};

//class Shape {
//
//};


#endif //FINALYEARPROJECT_MESH_H
