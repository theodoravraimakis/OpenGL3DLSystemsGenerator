//
// Created by Theodora Vraimakis on 12/03/2023.
//

#include "OBJExport.h"
struct compareVec {
    bool operator()(const glm::vec3& x, const glm::vec3& y) const {
        if (x.r < y.r) return true;
        if (x.r > y.r) return false;
        if (x.g < y.g) return true;
        if (x.g > y.g) return false;
        return (x.b < y.b);
    }
};

bool OBJExport::exportToOBJ(const MeshData& meshData, std::string& fileName)
{
    std::ofstream outFile("../objects/" + fileName + ".obj");
    std::ofstream mtlFile("../objects/" + fileName + ".mtl");
    if (!outFile.is_open())
    {
        std::cerr << "Could not export file: " << fileName << std::endl;
        return false;
    }

    outFile << "mtllib " << fileName << ".mtl" << std::endl;

    std::map<glm::vec3, std::string, compareVec> materialMap;
    size_t materialIndex = 1;

    for (const auto& color : meshData.colors) {
        auto it = materialMap.find(color);
        if (it == materialMap.end()) {
            std::ostringstream ss;
            ss << "color" << materialIndex;
            std::string materialName = ss.str();

            mtlFile << "newmtl " << materialName << std::endl;
            mtlFile << "Kd " << color.r << " " << color.g << " " << color.b << std::endl;

            materialMap[color] = materialName;
            materialIndex++;
        }
    }

    mtlFile.close();

    for (const auto& position : meshData.positions)
    {
        outFile << "v " << position.x << " " << position.y << " " << position.z << std::endl;
    }

    for (const auto& normal : meshData.normals)
    {
        outFile << "vn " << normal.x << " " << normal.y << " " << normal.z << std::endl;
    }

    for (size_t i = 0; i < meshData.positions.size(); i += 3) {
        glm::vec3 color = meshData.colors[i];
        std::string materialName = materialMap[color];
        outFile << "usemtl " << materialName << std::endl;
        outFile << "f " << i + 1 << "//" << i + 1 << " " << i + 2 << "//" << i + 2 << " " << i + 3 << "//" << i + 3 << std::endl;
    }

    outFile.close();

    std::cout << "Successfully exported mesh to: " << fileName << std::endl;
    return true;
}

MeshData OBJExport::loadOBJ(const std::string& fileName) {
    auto result = rapidobj::ParseFile(fileName + ".obj");
    if (result.error) {
        throw std::runtime_error(result.error.code.message());
    }
    rapidobj::Triangulate(result);
    MeshData ret;

    for (auto const& shape : result.shapes)
    {
        for (size_t i = 0; i < shape.mesh.indices.size(); i++)
        {
            auto const& idx = shape.mesh.indices[i];

            ret.positions.emplace_back(
                    glm::vec3{ result.attributes.positions[idx.position_index * 3 + 0],
                               result.attributes.positions[idx.position_index * 3 + 1],
                               result.attributes.positions[idx.position_index * 3 + 2]
                    });
            ret.normals.emplace_back(
                    glm::vec3{ result.attributes.normals[idx.normal_index * 3 + 0],
                               result.attributes.normals[idx.normal_index * 3 + 1],
                               result.attributes.normals[idx.normal_index * 3 + 2]
                    });
            auto const& mat = result.materials[shape.mesh.material_ids[i / 3]];

            ret.colors.emplace_back(glm::vec4{ mat.diffuse[0],mat.diffuse[1], mat.diffuse[2], mat.dissolve });

        }
    }
    std::cout << "Successfully loaded mesh from: " << fileName << std::endl;
    return ret;
}
#define STB_IMAGE_IMPLEMENTATION
#include <../stb-src/stb_image.h>

GLuint OBJExport::loadTexture(const std::string& fileName, int desiredChannels)
{
    GLuint texture = 0;
    int width, height, nrChannels;

    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &nrChannels, desiredChannels);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (imageData)
    {
        if (desiredChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else {
        std::cout << "Could not load texture from: " << fileName << std::endl;
    }
    stbi_image_free(imageData);
    return texture;
}
