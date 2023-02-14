//
// Created by Theodora Vraimakis on 12/02/2023.
//

#include "Mesh.h"

GLuint Mesh::createVAO(MeshData const& aMeshData)
{
    GLuint VAO = 0;

    GLuint positionVBO = 0;
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, aMeshData.positions.size() * sizeof(glm::vec3), aMeshData.positions.data(), GL_STATIC_DRAW);

    GLuint colorVBO = 0;
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, aMeshData.colors.size() * sizeof(glm::vec4), aMeshData.colors.data(), GL_STATIC_DRAW);

    GLuint normalVBO = 0;
    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, aMeshData.normals.size() * sizeof(glm::vec3), aMeshData.normals.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glVertexAttribPointer(
            0,
            3, GL_FLOAT, GL_FALSE,
            0,
            nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glVertexAttribPointer(
            1,
            4, GL_FLOAT, GL_FALSE,
            0,
            nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glVertexAttribPointer(
            2,
            3, GL_FLOAT, GL_FALSE,
            0,
            nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &colorVBO);
    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &normalVBO);
    return VAO;
}

MeshData Mesh::concatenate( MeshData aM, MeshData const& aN )
{
    aM.positions.insert( aM.positions.end(), aN.positions.begin(), aN.positions.end() );
    aM.colors.insert( aM.colors.end(), aN.colors.begin(), aN.colors.end() );
    return aM;
}


