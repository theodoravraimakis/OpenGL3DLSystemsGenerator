//
// Created by Theodora Vraimakis on 11/02/2023.
//

#ifndef FINALYEARPROJECT_ARCBALLCAMERA_H
#define FINALYEARPROJECT_ARCBALLCAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
//#include "glm/ext/quaternion_common.inl"
//#include "cmath"
//#include "GLFW/glfw3.h"
#include "../Config/Config.h"
#include "../Window/Window.h"
#include "iostream"

class ArcballCamera {
public:
    ArcballCamera(
            GLFWwindow* window,
            const glm::fvec4& pos,
            const glm::fvec4& target,
            float FOV,
            float ratio
            );
    ~ArcballCamera();
    void processInput(float deltaTime);
    const glm::mat4& getProjectionM() const;
    const glm::mat4& getViewM();
    glm::mat4 getUpdatedProjMatrix(float newFOV, float newRatio);
    const float& getFOV() const;
    const glm::fvec4& getPos() const;
    const glm::fvec4& getTargetPos() const;
    void setFOV(const float& newFOV);
    void setPos(const glm::fvec4& pos);
    void setTargetPos(const glm::fvec4& targetPos);

    void saveCursorPos();

    void updateCameraPos(glm::mat4& newRot);


    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


protected:

    // Observer pointer
    GLFWwindow* m_opWindow;

    float       m_FOV;
    float       m_ratio;
    glm::fvec4  m_pos;
    glm::fvec4  m_newPos;
    glm::fvec4  m_targetPos;
    glm::mat4   m_view;
    glm::mat4   m_proj{};

    glm::vec3 m_upVector;
    glm::vec3 axis_in_object_coord;
    glm::vec3 m_rightVector;
    glm::vec3 v;


private:
    glm::vec3 getArcballVector(float x, float y);

    glm::fvec2 m_lastCursorPos{};
    glm::fvec2 m_currentCursorPos{};


    friend class UI;
    friend class Window;
};


#endif //FINALYEARPROJECT_ARCBALLCAMERA_H
