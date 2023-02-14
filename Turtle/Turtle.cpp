////
//// Created by Theodora Vraimakis on 14/02/2023.
////
//
#include "Turtle.h"


void Turtle::computeFinalWorldM() {
    for (unsigned int i = 1; i < worldMatrices.size(); i++) {
        finalWorldMatrices[i] = finalWorldMatrices[parentVectors[i]] * worldMatrices[i];
    }
}

std::vector<glm::mat4> Turtle::returnFinalWorldM() {
    return  finalWorldMatrices;
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

//void Turtle::draw() {
//    for (unsigned int i = 1; i < finalWorldMatrices.size(); i++)
//    {
//        projCameraWorld = projection * world2camera * finalWorldMatrices[i];
//        Mat33f normalMatrix = glm::mat3(inverse(transpose(finalWorldMatrices[i])));
//
////        glUniformMatrix4fv(1, 1, GL_TRUE, finalWorldMatrices[i].v);
////        glUniformMatrix3fv(6, 1, GL_TRUE, normalMatrix.v);
////        glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
////
////        glUniform1f(location8, matDiffuse2.shininess);
////        if (parents[i] > 3) glBindVertexArray(leafs);
////        glDrawArrays(GL_TRIANGLES, 0, vertexCountRootCylinder * 3);
//    }
//}

//if (state.treeControl.pause) state.treeControl.speedMultiplier = 0.0f;
//else if (!state.treeControl.pause) state.treeControl.speedMultiplier = 2.0f;
//if (state.treeControl.speedUp) state.treeControl.speedMultiplier += 5.0f;
//else if (state.treeControl.speedDown) state.treeControl.speedMultiplier -= 1.0f;
//if (!state.treeControl.pause && state.treeControl.speedMultiplier < 1.f) state.treeControl.speedMultiplier = 1.f;
//else if (state.treeControl.speedMultiplier > 200.f) state.treeControl.speedMultiplier = 200.f;
//
//float windSpeed = static_cast<float>(state.treeControl.speedMultiplier * state.camControl.deltaTime);
//ImGui::SliderFloat("windSpeed", &windSpeed, 0.0f, 1.0f);
//
//for (int i = 3; i < 132; i++) //leafs
//{
//state.treeControl.wind += -0.005 * windSpeed;
//
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_z(-1.0 * kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_z(kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_x(-1.0 * kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_x(kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_y(-1.0 * kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//worlds.emplace_back(make_translation({ 0.f, 4.f, 0.f }) * make_rotation_y(kPi_ / 6.f + (sin(state.treeControl.wind) / 6)));
//parents.emplace_back(i);
//}
//
//std::vector<Mat44f> computed_worlds{ worlds.size(), kIdentity44f };
//
//for (unsigned int i = 1; i < worlds.size(); i++) {
//computed_worlds[i] = computed_worlds[parents[i]] * worlds[i];
//}
//
//for (unsigned int i = 1; i < computed_worlds.size(); i++)
//{
//projCameraWorld = projection * world2camera * computed_worlds[i];
//Mat33f normalMatrix = mat44_to_mat33(invert(transpose(computed_worlds[i])));
//glUniformMatrix4fv(1, 1, GL_TRUE, computed_worlds[i].v);
//glUniformMatrix3fv(6, 1, GL_TRUE, normalMatrix.v);
//glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
//
//glUniform1f(location8, matDiffuse2.shininess);
//if (parents[i] > 3) glBindVertexArray(leafs);
//glDrawArrays(GL_TRIANGLES, 0, vertexCountRootCylinder * 3);
//}