//
// Created by Theodora Vraimakis on 12/02/2023.
//

#include "Cylinder.h"
#include "iostream"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

Cylinder::Cylinder(
//        bool cap,
//        int count,
//        glm::vec3 color,
//        glm::mat4 transformations
        ) {
//    m_mesh = MeshData{vertices, colors, normals};
    makeCylinder(true, 128, { 0.48f, 0.33f, 0.25f }, glm::mat4(1.0f));
//    m_color = { 0.48f, 0.33f, 0.25f };
//    m_mesh = {};
};
void Cylinder::makeCylinder(
            bool cap,
            int count,
            glm::vec3 color,
            glm::mat4 transformations
        ) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    m_color = color;
    m_cap = cap;
    m_count = count;
    m_transformations = glm::mat4(1.0f);
    m_change = m_cap;
    glm::vec4 aColor = glm::vec4(color, 1.0f);
    float prevY = cos(0.f);
    float prevZ = sin(0.f);

    for (size_t i = 0; i < count; i++) {
        float const angle = (float) (i + 1) / float(count) * 2.f * 3.1415926f;
        float y = cos(angle);
        float z = sin(angle);

        vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.f, y, z));
        vertices.emplace_back(glm::vec3(1.f, prevY, prevZ));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

        vertices.emplace_back(glm::vec3(0.f, y, z));
        vertices.emplace_back(glm::vec3(1.f, y, z));
        vertices.emplace_back(glm::vec3(1.f, prevY, prevZ));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

        //Create caps of the cylinder
        if (cap) {
            vertices.emplace_back(glm::vec3(0.f, y, z));
            vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));

            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));

            vertices.emplace_back(glm::vec3(1.f, prevY, prevZ));
            vertices.emplace_back(glm::vec3(1.f, y, z));
            vertices.emplace_back(glm::vec3(1.f, 0.f, 0.f));

            normals.emplace_back(glm::vec3(1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(1.f, 0.f, 0.f));
        }
        prevY = y;
        prevZ = z;
    }
    for (auto& p : vertices)
    {
        glm::vec4 p4{ p.x, p.y, p.z, 1.f };
        glm::vec4 t = transformations * p4;
        t /= t.w;

        p = glm::vec3(t.x, t.y, t.z);
    }
    glm::mat3 const N = glm::mat3(transpose(inverse(transformations)));

    for (auto& n : normals)
    {
        glm::vec3 t = N * n;
        glm::vec4 t2 = { t.x, t.y, t.z, 1.0 };
        t2 /= t2.w;

        n = glm::vec3(t2.x, t2.y, t2.z);
    }
    std::vector col(vertices.size(), aColor);

    m_mesh.positions = std::move(vertices);
    m_mesh.colors = std::move(col);
    m_mesh.normals = std::move(normals);

//    return m_mesh;
}
// MeshData Cylinder::makeUpdatedCylinder(
//        bool cap,
//        int count,
//        glm::vec3 color,
//        glm::mat4 transformations
//) {
//     makeCylinder(cap, count, color, transformations);
//}
MeshData Cylinder::getMesh()
{
    return m_mesh;
}
glm::vec3 Cylinder::getColor()
{
//    return glm::vec3(m_mesh.colors[0]);
return m_color;
}
void Cylinder
::setColor(const glm::vec3 newCol)
{
    m_color = newCol;
}
void Cylinder
::updateCap()
{
    if (m_cap != m_change)
    {
        m_cap = m_change;
        updateMesh();
        updateVAO();
    }
}
MeshData Cylinder::updateColor(glm::vec4 newCol)
{
    std::vector newColors(m_mesh.positions.size(), newCol);
    MeshData mesh = {
            m_mesh.positions,
            std::move(newColors),
            m_mesh.normals,
    };
    m_mesh = mesh;
    return mesh;
}
void Cylinder::updateMesh()
{
    makeCylinder(m_cap, m_count, m_color, m_transformations);
}
void Cylinder::createVAO()
{
//    m_mesh.positions.clear();
//    m_mesh.colors.clear();
//    m_mesh.normals.clear();
   Mesh::createVAO(m_mesh);
}
//void Cylinder::updateVAO(MeshData mesh) {
//    glDeleteBuffers(1, &m_VAO);
//    GLuint v = Mesh::createVAO(mesh);
//    glBindVertexArray(v);
//}
void Cylinder::updateVAO() {
//    glDeleteBuffers(1, &m_VAO);
    m_VAO = Mesh::createVAO(m_mesh);
    glBindVertexArray(m_VAO);
//    m_VAO = v;
}
GLuint Cylinder::returnVAO()
{
    createVAO();
    return m_VAO;
}
size_t Cylinder::returnVertexCount()
{
    return m_mesh.positions.size();
}

bool Cylinder::getCap() const
{
    return m_cap;
}

Cylinder::~Cylinder()
= default;