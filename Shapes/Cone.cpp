//
// Created by Theodora Vraimakis on 14/02/2023.
//

#include "Cone.h"


Cone::Cone(
        bool cap,
        int count,
        glm::vec3 color,
        glm::mat4 transformations
        ) {
    makeCone(cap, count, color, transformations);
};
void Cone::makeCone(
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
    m_transformations = transformations;
    m_change = m_cap;
    glm::vec4 aColor = glm::vec4(color, 1.0f);

    float prevY = cos(0.f);
    float prevZ = sin(0.f);

    for (size_t i = 0; i < count; i++) {
        float const angle = (float) (i + 1) / float(count) * 2.f * 3.1415926f;
        float y = cos(angle);
        float z = sin(angle);

//        vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
//        vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
//        vertices.emplace_back(glm::vec3(1.f, 1.f, 1.f));
        vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.f, y, z));
        vertices.emplace_back(glm::vec3(1.f, 0.0f, 0.0f));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

//        vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
//        vertices.emplace_back(glm::vec3(1.f, y, z));
//        vertices.emplace_back(glm::vec3(1.f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.0f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.0f, y, z));
        vertices.emplace_back(glm::vec3(1.f, 0.0f, 0.0f));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

        //Create cap of the Cone
        if (cap) {
//            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
//            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
//            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
            vertices.emplace_back(glm::vec3(0.f, y, z));
            vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));

            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));

//            vertices.emplace_back(glm::vec3(1.f, prevY, prevZ));
//            vertices.emplace_back(glm::vec3(1.f, y, z));
//            vertices.emplace_back(glm::vec3(1.f, 0.f, 0.f));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));

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

    m_coneMesh.positions = std::move(vertices);
    m_coneMesh.colors = std::move(col);
    m_coneMesh.normals = std::move(normals);
}
MeshData Cone::getMesh()
{
    return m_coneMesh;
}
glm::vec3 Cone::getColor()
{
    return m_color;
}
void Cone
::setColor(const glm::vec3 newCol)
{
    m_color = newCol;
}
void Cone
::updateCap()
{
    if (m_cap != m_change)
    {
        m_cap = m_change;
        updateMesh();
        updateVAO();
    }
}
MeshData Cone::updateColor(glm::vec4 newCol)
{
    std::vector newColors(m_coneMesh.positions.size(), newCol);
    MeshData mesh = {
            m_coneMesh.positions,
            std::move(newColors),
            m_coneMesh.normals,
    };
    m_coneMesh = mesh;
    return mesh;
}
void Cone::updateMesh()
{
    makeCone(m_cap, m_count, m_color, m_transformations);
}
void Cone::createVAO()
{
    m_VAO = Mesh::createVAO(m_coneMesh);
}
void Cone::updateVAO() {
//    glDeleteBuffers(1, &m_VAO);
    m_VAO = Mesh::createVAO(m_coneMesh);
    glBindVertexArray(m_VAO);
//    m_VAO = v;
}
GLuint Cone::returnVAO()
{
    createVAO();
    return m_VAO;
}
size_t Cone::getVertexCount()
{
    return m_coneMesh.positions.size();
}

bool Cone::getCap() const
{
    return m_cap;
}

Cone::~Cone() {
    m_coneMesh.colors.clear();
    m_coneMesh.normals.clear();
    m_coneMesh.positions.clear();
};