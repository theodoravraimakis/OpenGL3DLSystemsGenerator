//
// Created by Theodora Vraimakis on 14/02/2023.
//

#ifndef FINALYEARPROJECT_TURTLE_H
#define FINALYEARPROJECT_TURTLE_H

#include "iostream"
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Shapes/Cylinder.h"
#include "../Shapes/Cone.h"
#include "../Shader/Shader.h"
#include <memory>
#include "../UI/UI.h"


class Turtle {
public:
    void treeTest();
    void computeFinalWorldM(
            const std::shared_ptr<Shape> &shape
            );
    void draw(
            const std::shared_ptr<Shader> &shader,
            const std::shared_ptr<Shape> &shape
            );

private:
    std::vector<glm::mat4> worldMatrices {
        glm::mat4(1.0f),
        glm::translate(glm::mat4(1.0f), glm::vec3( 0.f, -5.f, 0.f)),
    };

    std::vector<int> parentVectors {
            0,
            0
    };

    std::vector<glm::mat4> finalWorldMatrices;

    std::shared_ptr<Shader>                         m_shader;
};


#endif //FINALYEARPROJECT_TURTLE_H
