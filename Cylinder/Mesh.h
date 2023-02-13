//
// Created by Theodora Vraimakis on 12/02/2023.
//

#ifndef FINALYEARPROJECT_MESH_H
#define FINALYEARPROJECT_MESH_H

#include "glm/glm.hpp"
#include "glad/glad.h"
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
};


#endif //FINALYEARPROJECT_MESH_H
