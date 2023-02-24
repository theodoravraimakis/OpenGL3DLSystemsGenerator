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

#include "iostream"
#include "string"


constexpr float kPi_ = 3.1415926f;

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

enum class ShapeType
{
    CYLINDER = 0,
    CONE = 1
};


class Shape {
public:
    Shape(const ShapeType& type)
    {
        m_type = type;
//        m_changeType = m_type;
//        m_change = m_cap;
        m_cap = true;
        m_diameter = 1.0f;
        m_count = 128;
        m_color = glm::vec3(0.48f, 0.33f, 0.25f);
        m_transformations = glm::rotate(glm::mat4(1.0f), kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f)) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(4.f, 0.5f, 0.5f));
    };
    ~Shape() {
        m_mesh.colors.clear();
        m_mesh.normals.clear();
        m_mesh.positions.clear();
    };
    virtual void make()
    {};
    ShapeType getType()
    {
        return m_type;
    }
    MeshData& getMesh()
    {
        return m_mesh;
    }
    glm::vec3& getColor()
    {
        return m_color;
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
        m_VAO = m.createVAO(m_mesh);
    }
    size_t getVertexCount()
    {
        return m_mesh.positions.size();
    }
    bool* getCap()
    {
        return &m_cap;
    }
    bool* changeCap() {
        return &m_change;
    }
    ShapeType changeType() {
        return m_changeType;
    }
    void setCap(bool newCap)
    {
        if (m_cap != newCap)
        {
            m_cap = newCap;
            make();
            createVAO();
//            getVAO();
        }
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


    ShapeType   m_changeType;
protected:
    ShapeType   m_type;
    bool        m_cap;
    float       m_diameter;
    int         m_count;
    glm::vec3   m_color;
    glm::mat4   m_transformations;
    GLuint      m_VAO;
    MeshData    m_mesh;
    Mesh        m;

    bool        m_change;
};

#endif //FINALYEARPROJECT_MESH_H
