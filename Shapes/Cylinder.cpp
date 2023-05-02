//
// Created by Theodora Vraimakis on 12/02/2023.
//

#include "Cylinder.h"

Cylinder::Cylinder(
        bool cap,
        float diameter,
        std::shared_ptr<float> length,
        int count,
        glm::vec3 color,
        glm::mat4 transformations
        ) : Shape {ShapeType::CYLINDER}
{
//    m_type =
    m_name = std::string("Cylinder");
    m_cap = cap;
    m_diameter = diameter;
    m_count = count;
    m_color = color;
    m_transformations = std::make_shared<glm::mat4>(transformations);
    make();
//    m_changeType = m_type;
//    m_change = m_cap;
//    make();
};

Cylinder::Cylinder(): Shape {
        ShapeType::CYLINDER}{
    m_name = std::string("Cylinder");
    m_diameter = 1.0f;
    make();
//    m_change = m_cap;
//    make();
};

void Cylinder::make() {
    m_change = m_cap;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcoords;
    glm::vec4 aColor = glm::vec4(m_color, 1.0f);


    for (size_t i = 0; i < m_count; i++) {
        float const angle1 = (float) i / (float) m_count * 2.0f * 3.1415926f;
        float const angle2 = (float) (i + 1) / (float) m_count * 2.0f * 3.1415926f;

        float y1 = cos(angle1);
        float z1 = sin(angle1);
        float y2 = cos(angle2);
        float z2 = sin(angle2);

        vertices.emplace_back(glm::vec3(0.f, y1, z1));
        vertices.emplace_back(glm::vec3(0.f, y2, z2));
        vertices.emplace_back(glm::vec3(1.f, y1 / m_diameter, z1 / m_diameter));
        vertices.emplace_back(glm::vec3(0.f, y2, z2));
        vertices.emplace_back(glm::vec3(1.f, y2 / m_diameter, z2 / m_diameter));
        vertices.emplace_back(glm::vec3(1.f, y1 / m_diameter, z1 / m_diameter));

        float u1 = (float) i / (float) m_count;
        float u2 = (float) (i + 1) / (float) m_count;
        float v1 = 0.0f;
        float v2 = 1.0f;

            texcoords.emplace_back(glm::vec2(u1, v1));
            texcoords.emplace_back(glm::vec2(u2, v1));
            texcoords.emplace_back(glm::vec2(u1, v2));
            texcoords.emplace_back(glm::vec2(u2, v1));
            texcoords.emplace_back(glm::vec2(u2, v2));
            texcoords.emplace_back(glm::vec2(u1, v2));

        normals.emplace_back(normalize(glm::vec3(0.f, y1, z1)));
        normals.emplace_back(normalize(glm::vec3(0.f, y2, z2)));
        normals.emplace_back(normalize(glm::vec3(0.f, y1, z1)));
        normals.emplace_back(normalize(glm::vec3(0.f, y2, z2)));
        normals.emplace_back(normalize(glm::vec3(0.f, y2, z2)));
        normals.emplace_back(normalize(glm::vec3(0.f, y1, z1)));

    }

    for (auto& p : vertices)
    {
        glm::vec4 p4{ p.x, p.y, p.z, 1.f };
        glm::vec4 t = *m_transformations * p4;
        t /= t.w;

        p = glm::vec3(t.x, t.y, t.z);
    }
    glm::mat3 const N = glm::mat3(transpose(inverse(*m_transformations)));

    for (auto& n : normals)
    {
        glm::vec3 t = N * n;
        glm::vec4 t2 = { t.x, t.y, t.z, 1.0 };
        t2 /= t2.w;

        n = glm::vec3(t2.x, t2.y, t2.z);
    }
    std::vector col(vertices.size(), aColor);
    m_mesh.colors = std::move(col);

    m_mesh.positions = std::move(vertices);
    m_mesh.normals = std::move(normals);
    m_mesh.textCoords = std::move(texcoords);

}
