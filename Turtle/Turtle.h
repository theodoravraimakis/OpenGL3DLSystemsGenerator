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


class Turtle {
public:
    void computeFinalWorldM();
    std::vector<glm::mat4> returnFinalWorldM();
    void draw(
            const std::shared_ptr<Shader> &shader,
//            const T &shape
            const std::shared_ptr<Shape> &shape
            );

private:
    std::vector<glm::mat4> worldMatrices {
        glm::mat4(1.0f),
        glm::translate(glm::mat4(1.0f), glm::vec3( 0.f, 0.f, 0.f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 3.f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 4.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (-kPi_ / 3.f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / -3.f), glm::vec3(1.0f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.0f), (kPi_ / 3.f), glm::vec3(1.0f, 0.0f, 0.0f))
    };

    std::vector<int> parentVectors {
            0,
            0,
            1,
            2,
            2,
            2,
            3,
            3,
    };

    std::vector<glm::mat4> finalWorldMatrices {
            worldMatrices.size(),
            glm::mat4(1.0f)
    };
    std::shared_ptr<Shader>                         m_shader;
    std::shared_ptr<Cylinder>                       m_cylinder;
    std::shared_ptr<Cone>                           m_cone;
};


#endif //FINALYEARPROJECT_TURTLE_H
