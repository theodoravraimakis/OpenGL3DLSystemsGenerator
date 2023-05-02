//
// Created by Theodora Vraimakis on 14/02/2023.
//

#include "Cone.h"


Cone::Cone(
        bool cap,
        float length,
        int count,
        glm::vec3 color,
        glm::mat4 transformations
        )
        : Shape(ShapeType::CONE) {

    m_cap = true;
//    m_diameter = 1.0f;
    m_count = count;
//    m_length = 5.0f; //TODO
    m_lengthPointer = std::make_shared<float>(length);
    m_color = color;
    m_transformations = std::make_shared<glm::mat4>(transformations);
    m_name = std::string("Cone");
    make();
//    m_cap = cap;
//    m_count = count;
//    m_color = color;
//    *m_transformations = transformations;
//    m_changeType = m_type;
//    m_change = m_cap;
//    make();
};
Cone::Cone(): Shape {
        ShapeType::CONE}{
    m_name = std::string("Cone");
    createVAO();
    make();
//    m_change = m_cap;
//    make();
};
void Cone::make() {
    m_change = m_cap;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    glm::vec4 aColor = glm::vec4(m_color, 1.0f);
    std::vector<glm::vec2> texcoords;

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

        float u1 = (float)i / (float)m_count;
        float u2 = (float)(i + 1) / (float)m_count;
        float v1 = 0.0f;
        float v2 = 1.0f;
//
        if (m_useTexture) {
            texcoords.emplace_back(glm::vec2(u1, v1));
            texcoords.emplace_back(glm::vec2(u2, v1));
            texcoords.emplace_back(glm::vec2(u1, v2));
            texcoords.emplace_back(glm::vec2(u2, v1));
            texcoords.emplace_back(glm::vec2(u2, v2));
            texcoords.emplace_back(glm::vec2(u1, v2));
        }
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

    if (!m_useTexture){
        std::vector col(vertices.size(), aColor);
        m_mesh.colors = std::move(col);
    }



    m_mesh.positions = std::move(vertices);

    m_mesh.normals = std::move(normals);
    m_mesh.textCoords = std::move(texcoords);

}