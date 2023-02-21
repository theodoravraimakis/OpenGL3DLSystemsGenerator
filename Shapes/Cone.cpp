//
// Created by Theodora Vraimakis on 14/02/2023.
//

#include "Cone.h"


Cone::Cone(
        bool cap,
        int count,
        glm::vec3 color,
        glm::mat4 transformations
        )
        : Shape(ShapeType::CONE) {
    m_cap = cap;
    m_count = count;
    m_color = color;
    m_transformations = transformations;
    make();
};
void Cone::make() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    m_change = m_cap;
    glm::vec4 aColor = glm::vec4(m_color, 1.0f);

    float prevY = cos(0.f);
    float prevZ = sin(0.f);

    for (size_t i = 0; i < m_count; i++) {
        float const angle = (float) (i + 1) / float(m_count) * 2.f * 3.1415926f;
        float y = cos(angle);
        float z = sin(angle);

        vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.f, y, z));
        vertices.emplace_back(glm::vec3(1.f, 0.0f, 0.0f));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

        vertices.emplace_back(glm::vec3(0.0f, prevY, prevZ));
        vertices.emplace_back(glm::vec3(0.0f, y, z));
        vertices.emplace_back(glm::vec3(1.f, 0.0f, 0.0f));

        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));
        normals.emplace_back(normalize(glm::vec3(0.f, y, z)));

        //Create cap of the Cone
        if (m_cap) {
            vertices.emplace_back(glm::vec3(0.f, y, z));
            vertices.emplace_back(glm::vec3(0.f, prevY, prevZ));
            vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));

            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));
            normals.emplace_back(glm::vec3(-1.f, 0.f, 0.f));

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
        glm::vec4 t = m_transformations * p4;
        t /= t.w;

        p = glm::vec3(t.x, t.y, t.z);
    }
    glm::mat3 const N = glm::mat3(transpose(inverse(m_transformations)));

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
}