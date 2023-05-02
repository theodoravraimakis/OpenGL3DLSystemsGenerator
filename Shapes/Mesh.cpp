//
// Created by Theodora Vraimakis on 12/02/2023.
//

#include "Mesh.h"
#include "../L-System/LSystem.h"
void Shape::makePolygon(const std::vector<Command>& commands) {\
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> colors;

    std::stack<glm::vec3> positionStack;
    std::stack<glm::vec3> directionStack;
    std::stack<std::vector<glm::vec3>> polygonStack;
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 direction = glm::vec3(1, 0, 0);

    for (auto command: commands) {
        switch (command.m_type) {
            case CommandType::FORWARD: {
                glm::vec3 nextPosition = position + m_polyLength * direction;
                if (!polygonStack.empty()) {
                    polygonStack.top().push_back(nextPosition);
                }
                position = nextPosition;
            }
                break;
            case CommandType::RIGHT:
                direction = glm::rotateZ(direction, glm::radians(m_polyAngle));
                break;
            case CommandType::LEFT:
                direction = glm::rotateZ(direction, glm::radians(-m_polyAngle));
                break;
            case CommandType::UP:
                direction = glm::rotateX(direction, glm::radians(-m_polyAngle));
                break;
            case CommandType::DOWN:
                direction = glm::rotateX(direction, glm::radians(m_polyAngle));
                break;
            case CommandType::CW:
                direction = glm::rotateY(direction, glm::radians(m_polyAngle));
                break;
            case CommandType::CCW:
                direction = glm::rotateY(direction, glm::radians(-m_polyAngle));
                break;
            case CommandType::TURN:
                direction = glm::rotateZ(direction, glm::radians(-180.0f));
                break;
            case CommandType::SKIP:
                position += m_polyLength * direction;
                break;
            case CommandType::START_POLYGON:
                polygonStack.push({});
                polygonStack.top().push_back(position);
                break;
            case CommandType::END_POLYGON:
                if (!polygonStack.empty()) {
                    auto polygon = polygonStack.top();
                    polygonStack.pop();
                    if (polygon.size() >= 3) {
                        for (size_t i = 2; i < polygon.size(); i++) {
                            // Add vertices to mesh
                            vertices.emplace_back(polygon[0]);
                            vertices.emplace_back(polygon[i - 1]);
                            vertices.emplace_back(polygon[i]);
                        }
                    }
                }
                break;
            default:
                break;
        }
    }

    for (size_t i = 0; i < vertices.size(); i += 3) {
        glm::vec3 v1 = vertices[i + 1] - vertices[i];
        glm::vec3 v2 = vertices[i + 2] - vertices[i];
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }

    std::vector col(vertices.size(), glm::vec4(m_color, 1.0f));
    m_mesh.colors = std::move(col);
    m_mesh.positions = std::move(vertices);
    m_mesh.normals = std::move(normals);

}

GLuint Mesh::createVAO(MeshData const& aMeshData, bool useTexture)
{
    GLuint VAO = 0;

    GLuint positionVBO = 0;
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, aMeshData.positions.size() * sizeof(glm::vec3), aMeshData.positions.data(), GL_STATIC_DRAW);

    GLuint textureBO = 0;
    GLuint colorBO = 0;
    if (useTexture)
    {
        glGenBuffers(1, &textureBO);
        glBindBuffer(GL_ARRAY_BUFFER, textureBO);
        glBufferData(GL_ARRAY_BUFFER, aMeshData.textCoords.size() * sizeof(glm::vec2), aMeshData.textCoords.data(), GL_STATIC_DRAW);
    }
    else
    {
        glGenBuffers(1, &colorBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorBO);
        glBufferData(GL_ARRAY_BUFFER, aMeshData.colors.size() * sizeof(glm::vec4), aMeshData.colors.data(), GL_STATIC_DRAW);
    }

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

    if (useTexture)
    {
        glBindBuffer(GL_ARRAY_BUFFER, textureBO);
        glVertexAttribPointer(
                1,
                2, GL_FLOAT, GL_FALSE,
                0,
                0);
        glEnableVertexAttribArray(1);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, colorBO);
        glVertexAttribPointer(
                3,
                4, GL_FLOAT, GL_FALSE,
                0,
                nullptr);
        glEnableVertexAttribArray(3);
    }

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glVertexAttribPointer(
            2,
            3, GL_FLOAT, GL_FALSE,
            0,
            nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    if (useTexture) {
        glDeleteBuffers(1, &textureBO);
    }
    else {
        glDeleteBuffers(1, &colorBO);
    }

    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &normalVBO);

    return VAO;
}
MeshData Mesh::concatenate( MeshData aM, MeshData const& aN )
{
    aM.positions.insert( aM.positions.end(), aN.positions.begin(), aN.positions.end() );
    aM.normals.insert( aM.normals.end(), aN.normals.begin(), aN.normals.end() );
    aM.colors.insert( aM.colors.end(), aN.colors.begin(), aN.colors.end() );
    return aM;
}


