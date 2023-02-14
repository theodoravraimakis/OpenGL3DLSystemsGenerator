//
// Created by Theodora Vraimakis on 12/02/2023.
//

#include "Cylinder.h"

Cylinder::Cylinder(
        bool cap,
        int count,
        glm::vec3 color,
        glm::mat4 transformations
        ) {
    makeCylinder(cap, count, color, transformations);
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
//    m_transformations = glm::mat4(1.0f);
    m_transformations = transformations;
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

    m_cylinderMesh.positions = std::move(vertices);
    m_cylinderMesh.colors = std::move(col);
    m_cylinderMesh.normals = std::move(normals);
}
MeshData Cylinder::getMesh()
{
    return m_cylinderMesh;
}
glm::vec3& Cylinder::getColor()
{
    return m_color;
}
void Cylinder
::setColor(glm::vec3& newCol)
{
    if (m_color != newCol)
    {
        m_color = newCol;
        updateMesh();
        updateVAO();
    }
}
void Cylinder
::updateCap(bool newCap)
{
//    if (m_cap != m_change)
//    {
//        m_cap = m_change;
//        updateMesh();
//        updateVAO();
//    }
    if (m_cap != newCap)
    {
        m_cap = newCap;
        updateMesh();
        updateVAO();
    }
}
MeshData Cylinder::updateColor(glm::vec4 newCol)
{
    std::vector newColors(m_cylinderMesh.positions.size(), newCol);
    MeshData mesh = {
            m_cylinderMesh.positions,
            std::move(newColors),
            m_cylinderMesh.normals,
    };
    m_cylinderMesh = mesh;
    return mesh;
}
void Cylinder::updateMesh()
{
    makeCylinder(m_cap, m_count, m_color, m_transformations);
}
void Cylinder::createVAO()
{
   m_VAO = m.createVAO(m_cylinderMesh);
}
void Cylinder::updateVAO() {
//    glDeleteBuffers(1, &m_VAO);
    m_VAO = m.createVAO(m_cylinderMesh);
    glBindVertexArray(m_VAO);
//    m_VAO = v;
}
GLuint Cylinder::getVAO()
{
    createVAO();
    return m_VAO;
}
size_t Cylinder::getVertexCount()
{
    return m_cylinderMesh.positions.size();
}

bool* Cylinder::getCap()
{
    return &m_cap;
}

bool* Cylinder::changeCap() {
    return &m_change;
}

Cylinder::~Cylinder() {
    m_cylinderMesh.colors.clear();
    m_cylinderMesh.normals.clear();
    m_cylinderMesh.positions.clear();
};