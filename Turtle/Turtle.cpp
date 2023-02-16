////
//// Created by Theodora Vraimakis on 14/02/2023.
////
//
#include "Turtle.h"



void Turtle::computeFinalWorldM() {
    treeTest();

    finalWorldMatrices = {
            worldMatrices.size(),
            glm::mat4(1.0f)
    };

    for (unsigned int i = 1; i < worldMatrices.size(); i++) {
        finalWorldMatrices[i] = finalWorldMatrices[parentVectors[i]] * worldMatrices[i];
    }
}

void Turtle::draw(
        const std::shared_ptr<Shader> &shader,
        const std::shared_ptr<Shape> &shape
        ) {
    glBindVertexArray(shape->getVAO());
    for (unsigned int i = 1; i < finalWorldMatrices.size(); i++)
    {
//        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
        shader->setMat4("model", finalWorldMatrices[i]);
        glDrawArrays(GL_TRIANGLES, 0, shape->getVertexCount() * 3);

    }
}

void Turtle::treeTest()
{
    std::vector<glm::mat4> branches = {
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)),
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)),
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 3.f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f)),
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (-kPi_ / 3.f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f)),
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / -3.f), glm::vec3(1.0f, 0.0f, 0.0f)),
            glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 3.f), glm::vec3(1.0f, 0.0f, 0.0f))
    };
    std::copy(begin(branches), end(branches), std::back_inserter(worldMatrices));

    std::vector<int> branchesParents = {
            1,
            2,
            2,
            2,
            3,
            3
    };
    std::copy(begin(branchesParents), end(branchesParents), std::back_inserter(parentVectors));

    for (int i = 3; i < 132; i++)
    {
        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / -6.f), glm::vec3(0.0f, 0.0f, 1.0f)));
        parentVectors.emplace_back(i);
        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 6.f), glm::vec3(0.0f, 0.0f, 1.0f)));
        parentVectors.emplace_back(i);

        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / -6.f), glm::vec3(1.0f, 0.0f, 0.0f)));
        parentVectors.emplace_back(i);
        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 6.f), glm::vec3(1.0f, 0.0f, 0.0f)));
        parentVectors.emplace_back(i);

        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / -6.f), glm::vec3(0.0f, 1.0f, 0.0f)));
        parentVectors.emplace_back(i);
        worldMatrices.emplace_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 6.f), glm::vec3(0.0f, 1.0f, 0.0f)));
        parentVectors.emplace_back(i);
    }
}
