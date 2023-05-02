//
// Created by Theodora Vraimakis on 05/03/2023.
//

#include "Output.h"


void Output::draw(
        const std::shared_ptr<Shader> &shader,
        std::shared_ptr<Shape> &shape,
        const std::shared_ptr<AllShapes> &allShapes,
        std::shared_ptr<Camera> &camera,
        std::shared_ptr<Textures> &textures

) {
    glm::vec3 sumPositions(0.0f);

    for (auto elem: getAllElements()) {
        bool oldTexture;
        if(*elem->m_useTexture)
        {

            if(oldTexture != *elem->m_useTexture)
                elem->m_shape->updateShape();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, elem->m_texture->location);
            GLuint useTextureLoc = glGetUniformLocation(shader->programId(), "useTexture");
            glUniform1i(useTextureLoc, 1); // set to 1 to enable texture, set to 0 to disable texture
            oldTexture = *elem->m_useTexture;
        }
        else
        {
            elem->m_shape->m_useTexture = elem->m_useTexture;
            GLuint useTextureLoc = glGetUniformLocation(shader->programId(), "useTexture");
            glUniform1i(useTextureLoc, 0); // set to 0 to disable texture
            oldTexture = *elem->m_useTexture;
        }

        elem->m_shape->setLength(elem->m_length);
        elem->m_shape->setWidth(elem->m_width);
        glBindVertexArray(elem->m_shape->getVAO());
        shader->setMat4("model", elem->m_mat);
        glDrawArrays(GL_TRIANGLES, 0, elem->m_shape->getVertexCount());

        auto position = glm::vec3(elem->m_mat[3]);
        sumPositions += position;
    }
    center = sumPositions / static_cast<float>(getAllElements().size());
}

void Output::concatenate(const std::shared_ptr<AllShapes> &allShapes)
{
    for (auto elem: allElements) {
        elem->m_shape->setLength(elem->m_length);
        MeshData transformedMesh = elem->m_shape->getMesh();
        transformedMesh.transform(elem->m_mat);

        concatenatedMesh = Mesh::concatenate(concatenatedMesh, transformedMesh);
        Mesh::clearMesh(transformedMesh);
        concatenatedMeshVAO = Mesh::createVAO(concatenatedMesh, *elem->m_shape->m_useTexture);
        concatenatedMeshVertexCount = concatenatedMesh.positions.size();
    }
}

void Output::addElement(std::shared_ptr<OutputElement> element) {
    allElements.push_back(element);
}

const std::vector<std::shared_ptr<OutputElement>>& Output::getAllElements() {
    return allElements;
}