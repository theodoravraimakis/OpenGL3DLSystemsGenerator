//
// Created by Theodora Vraimakis on 14/02/2023.
//

#ifndef FINALYEARPROJECT_TURTLE_H
#define FINALYEARPROJECT_TURTLE_H

#include "iostream"
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Turtle {
public:
    void computeFinalWorldM();
    std::vector<glm::mat4> returnFinalWorldM();

private:
    std::vector<glm::mat4> worldMatrices {
        glm::mat4(1.0f),
        glm::translate(glm::mat4(1.0f), glm::vec3( 0.f, 4.f, 0.f)),
        glm::translate(glm::mat4(1.0f), glm::vec3( 0.f, 4.f, 0.f))
    };

    std::vector<int> parentVectors {
        0,
        0,
        1
    };

    std::vector<glm::mat4> finalWorldMatrices {
            worldMatrices.size(),
            glm::mat4(1.0f)
    };
};


#endif //FINALYEARPROJECT_TURTLE_H
