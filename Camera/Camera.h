//
// Created by Theodora Vraimakis on 11/02/2023.
//

#ifndef FINALYEARPROJECT_CAMERA_H
#define FINALYEARPROJECT_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

#include "../Config/Config.h"
#include "../Window/Window.h"

#include "iostream"

class Camera {
public:
    Camera(
            GLFWwindow* window,
            glm::fvec4& pos,
            glm::fvec4& target,
            float FOV,
            float ratio
    );
    ~Camera();
    const glm::mat4& getProjectionM() const;
    const glm::mat4& getViewMat();
    glm::mat4 getNewProjMat(float newFOV, float newRatio);
    const float& getFOV() const;
    glm::fvec4& getPos() ;
    glm::fvec4& getObjectPos() ;
    void setFOV(const float& newFOV);
    void setPos(const glm::fvec4& pos);
    void setObjectPos(const glm::fvec4& objectPos);
    void saveCursor();
    void update();

    GLFWwindow* m_window;
    float       m_FOV;
    float       m_ratio;
    glm::fvec4  m_pos;
    glm::fvec4  m_newPos{};
    glm::vec4   m_objectPos;
    glm::mat4   m_view{};
    glm::mat4   m_prevView{};
    glm::mat4   m_proj{};
    glm::vec3   m_rightVec{};
    glm::fvec2  m_prevCursor{};
    glm::fvec2 m_currentCursor{};

private:
    glm::vec3 getArcballVec(float x, float y);
    void updateViewMat();

    friend class UI;
    friend class Window;
};

#endif //FINALYEARPROJECT_CAMERA_H
