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
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <vector>
#include <memory>

#include "iostream"
#include "string"
#include <stack>



class Command;
enum class CommandType;


constexpr float kPi_ = 3.1415926f;

struct Material {
    std::string name;
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(1.0f);
    float shininess = 0.0f;
};

struct MeshData
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec3> normals;


    std::vector<glm::vec2> textCoords;
    GLuint texture = 100;

    void transform(const glm::mat4& transformMatrix)
    {
        for (glm::vec3& position : positions)
        {
            glm::vec4 transformedPosition = transformMatrix * glm::vec4(position, 1.0f);
            position = glm::vec3(transformedPosition);
        }

        for (glm::vec3& normal : normals)
        {
            glm::vec4 transformedNormal = glm::transpose(glm::inverse(transformMatrix)) * glm::vec4(normal, 0.0f);
            normal = glm::normalize(glm::vec3(transformedNormal));
        }
    }
};

class Mesh {
public:
    static GLuint createVAO(MeshData const& aMeshData, bool useTexture);
    static MeshData concatenate(MeshData aM, MeshData const& aN );
    inline static void clearMesh(MeshData& mesh) {
        mesh.colors.clear();
        mesh.normals.clear();
        mesh.positions.clear();
    }
};

enum class ShapeType
{
    CYLINDER = 0,
    CONE = 1,
    TRIANGLE = 2
};


class Shape {
public:
    Shape(const ShapeType& type)
    {
        m_useTexture = std::make_shared<bool>(false);
        m_type = type;
        m_cap = true;
        m_diameter = 1.0f;
        m_count = 20;
        m_length = 0.1f;
        m_width = 0.01f;
        m_color = glm::vec3(0.48f, 0.33f, 0.25f);
        m_transformations = std::make_shared<glm::mat4>(glm::rotate(glm::mat4(1.0f), kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f)) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(m_length, m_width, m_width)))
                            ;

        m_polyLength = 0.1f;
        m_polyAngle = 90.0f;
    };
    ~Shape() {
        m_mesh.colors.clear();
        m_mesh.normals.clear();
        m_mesh.positions.clear();
    };

    virtual void make()
    {};
    void makePolygon(const std::vector<Command>& commands);
    MeshData& getMesh()
    {
        return m_mesh;
    }
    glm::vec3& getColor()
    {
        return m_color;
    }
    float& getLength()
    {
        return m_length;
    }
    float& getWidth()
    {
        return m_width;
    }
    float& getPolygonLength()
    {
        return m_polyLength;
    }
    float& getPolygonAngle()
    {
        return m_polyAngle;
    }
    GLuint getVAO()
    {
        return m_VAO;
    };
    GLuint* getPointerVAO()
    {
        return &m_VAO;
    };
    void createVAO()
    {
        m_VAO = Mesh::createVAO(m_mesh, *m_useTexture);
    }
    size_t getVertexCount()
    {
        return m_mesh.positions.size();
    }
    void setColor(glm::vec3& newCol)
    {
        if (m_color != newCol)
        {
            m_color = newCol;

            make();
            createVAO();
        }
    }
    void setLength(float& newLength)
    {
        if (m_length != newLength)
        {
            m_length = newLength;

            m_transformations = std::make_shared<glm::mat4>(
                    glm::rotate(glm::mat4(1.0f), kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f)) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(m_length, m_width, m_width)));
            updateShape();
        }
    }
    void setWidth(float newWidth)
    {
        if (m_width != newWidth)
        {
            m_width = newWidth;
            m_transformations = std::make_shared<glm::mat4>(
                    glm::rotate(glm::mat4(1.0f), kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f)) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(m_length, m_width, m_width)));
            updateShape();
        }
    }
    void setPolyLength(float newLength)
    {
        if (m_polyLength != newLength)
        {
            m_polyLength = newLength;
        }
    }
    void setPolyAngle(float newAngle)
    {
        if (m_polyAngle != newAngle)
        {
            m_polyAngle = newAngle;
        }
    }

    void updateShape()
    {
        make();
        createVAO();
    }

    void updatePolygon(const std::vector<Command>& commands)
    {
        makePolygon(commands);
        createVAO();
    }

    ShapeType   m_type;
    bool        m_cap;
    float       m_diameter;
    float       m_length;
    float       m_width;
    std::shared_ptr<float> m_lengthPointer;
    int         m_count;
    glm::vec3   m_color;
    std::shared_ptr<glm::mat4>   m_transformations;
    GLuint      m_VAO;
    MeshData    m_mesh;
    Mesh        m;

    bool        m_change;
    std::string m_name;
    std::shared_ptr<bool> m_useTexture;

    float m_polyLength;
    float m_polyAngle;
};



#endif //FINALYEARPROJECT_MESH_H
