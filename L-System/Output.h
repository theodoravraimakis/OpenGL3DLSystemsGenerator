//
// Created by Theodora Vraimakis on 05/03/2023.
//

#ifndef FINALYEARPROJECT_OUTPUT_H
#define FINALYEARPROJECT_OUTPUT_H

#include "iostream"
#include "glm/glm.hpp"
#include "LSystem.h"

class OutputElement;
class AllShapes;
class Command;
class LSystem;
#include "../Shapes/Cylinder.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Export/OBJExport.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/component_wise.hpp>

class Camera;

class Output {
public:
    void draw(
            const std::shared_ptr<Shader> &shader,
            std::shared_ptr<Shape> &shape,
            const std::shared_ptr<AllShapes> &allShapes,
            std::shared_ptr<Camera> &camera,
            std::shared_ptr<Textures> &textures
    );
    void concatenate(const std::shared_ptr<AllShapes> &allShapes);

    MeshData concatenatedMesh;
    GLuint concatenatedMeshVAO;
    int concatenatedMeshVertexCount;

    glm::vec3 center;
    float distance;
    GLuint grassTexture = OBJExport::loadTexture("../textures/treeTexture.jpeg", 4);


    void addElement(std::shared_ptr<OutputElement> element);
    const std::vector<std::shared_ptr<OutputElement>>& getAllElements();
    std::shared_ptr<std::string> g= std::make_shared<std::string>("");
private:
    std::vector<std::shared_ptr<OutputElement>> allElements;
    std::vector<std::shared_ptr<Shape>> segmentTypes;


};


#endif //FINALYEARPROJECT_OUTPUT_H
