//
// Created by Theodora Vraimakis on 11/02/2023.
//

#ifndef FINALYEARPROJECT_ARCBALLCAMERA_H
#define FINALYEARPROJECT_ARCBALLCAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"
#include "../Config.h"

class ArcballCamera {
public:
    ArcballCamera(
            GLFWwindow* window,
            glm::vec4 pos,
            glm::vec4 target,
            float FOV
            );
    ~ArcballCamera();
    const glm::mat4& getProjectionM() const;
    const glm::mat4& getViewM();
    static glm::mat4 getUpdatedProjMatrix(float newFOV);
    const float& getFOV() const;
    glm::vec4 getPos() const;
    void setFOV(float newFOV);
    void setPos(glm::vec4 pos);
    void setTargetPos(glm::vec4 targetPos);

    void saveCursorPos();

    void updateCameraPos(glm::mat4& newRot);

    glm::vec4 getTargetPos() const;

protected:

    // Observer pointer
    GLFWwindow* m_opWindow;

    float       m_FOV;
    glm::vec4  m_pos;
    glm::vec4  m_targetPos;
    glm::mat4   m_view{};
    glm::mat4   m_proj{};

private:
    glm::vec3 getArcballVector(float x, float y);

    glm::fvec2 m_lastCursorPos;
    glm::fvec2 m_currentCursorPos;
};


#endif //FINALYEARPROJECT_ARCBALLCAMERA_H
