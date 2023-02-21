//
// Created by Theodora Vraimakis on 11/02/2023.
//

#include "ArcballCamera.h"

ArcballCamera::ArcballCamera
(
        GLFWwindow* window,
        const glm::fvec4& pos,
        const glm::fvec4& target,
        const float FOV,
        const float ratio
) : m_opWindow(window),
    m_FOV(FOV),
    m_ratio(ratio),
    m_pos(pos),
    m_targetPos(target)
{
    m_rightVector = glm::vec3(0.0f, 1.0f, 0.0f);
//    m_newPos = m_pos;

    m_proj = getUpdatedProjMatrix(
            glm::radians(m_FOV),
            m_ratio
    );

    m_lastCursorPos = glm::vec2(0.0f);
    m_currentCursorPos = glm::vec2(0.0f);
    m_targetPos = glm::vec4(0.0f);
}

ArcballCamera::~ArcballCamera() = default;

const glm::mat4& ArcballCamera
::getProjectionM() const
{
    return m_proj;
}

const glm::mat4& ArcballCamera
::getViewM()
{
    // First we update the view matrix if the ArcballCamera
    // position changed.
    // TODO: verify if it changed it.

//    glm::vec4 p = getPos();
//    if (p != m_newPos) {
//        setPos(m_newPos);
//    }
    m_view = glm::lookAt(
            // Eyes position.
            glm::vec3(m_pos),
            // Center position
            glm::vec3(m_targetPos),
            // Up axis
            glm::vec3(0.0f, 1.0f, 0.0f)
    );

    return m_view;

}

const float& ArcballCamera
::getFOV() const
{
    return m_FOV;
}

glm::mat4 ArcballCamera::getUpdatedProjMatrix(
        const float newFOV,
        const float newRatio
) {

        glm::mat4 proj = glm::perspective(
                newFOV,
                newRatio, 0.1f, 100.0f
        );
    return proj;
}

void ArcballCamera
::setFOV(const float& newFOV)
{
    m_FOV = newFOV;

    m_proj = getUpdatedProjMatrix(glm::radians(newFOV), m_ratio);
}

void ArcballCamera
::setPos(const glm::vec4& pos)
{
    m_pos = pos;
}

void ArcballCamera
::setTargetPos(const glm::vec4& targetPos)
{
    m_targetPos = targetPos;
}

const glm::fvec4& ArcballCamera
::getPos() const
{
    return m_pos;
}

const glm::fvec4& ArcballCamera
::getTargetPos() const
{
    return m_targetPos;
}

glm::vec3 ArcballCamera::getArcballVector(const float x, float y)
{
    glm::vec3 P = glm::vec3(
            1.0f * x / (float)Config::SCR_WIDTH * 2.0f - 1.0f,
            -1.0f * (1.0f * y / (float)Config::SCR_HEIGHT * 2.0f - 1.0f),
            0.0f
    );

    float OPsquared = P.x * P.x + P.y * P.y;

    if (OPsquared <= 1.0f)
    {
        // Pythagoras
        P.z = glm::sqrt(1.0f - OPsquared);
    } else
    {
        // Nearest point.
        P = glm::normalize(P);
    }

    return P;
}

/*
 * Algorithm taken from:
 * https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
 */
void ArcballCamera::updateCameraPos(glm::mat4& newRot) {
    double x, y;
    glfwGetCursorPos(m_opWindow, &x, &y);

    m_currentCursorPos = glm::vec2(x, y);
        if (x != m_lastCursorPos.x || y != m_lastCursorPos.y) {
            glm::vec3 v1 = getArcballVector(m_lastCursorPos.x, m_lastCursorPos.y);
            glm::vec3 v2 = getArcballVector((float) x, (float) y);

            float angle = glm::acos(glm::min(1.0f, glm::dot(v1, v2))) * 0.02f;


            glm::vec3 axis_in_camera_coord = glm::cross(v1, v2);
                axis_in_camera_coord = glm::normalize(axis_in_camera_coord);
//            }
            glm::mat3 camera2object = glm::inverse(glm::mat3(getViewM()) * glm::mat3(newRot));
            axis_in_object_coord = camera2object * axis_in_camera_coord;
            newRot = glm::rotate(newRot, glm::degrees(angle), axis_in_object_coord);

            m_lastCursorPos = m_currentCursorPos;
            m_pos = newRot * m_pos;
//            m_pos = newRot * m_pos;
        }
//    setPos(newRot * m_pos);
}

void ArcballCamera::saveCursorPos()
{
    double x, y;

    glfwGetCursorPos(m_opWindow, &x, &y);

    m_currentCursorPos = m_lastCursorPos = glm::vec2(x, y);
}

void ArcballCamera::processInput(float deltaTime)
{
    auto cameraSpeed = static_cast<float>(2.5 * deltaTime);
    glm::vec3 pos = getPos();
    std::vector<float*> cameraPosition =
            {
                    &pos.x,
                    &pos.y,
                    &pos.z
            };
    if (glfwGetKey(m_opWindow, GLFW_KEY_UP ) == GLFW_PRESS){
        pos += cameraSpeed * cameraFront;
    }
// Move backward
    if (glfwGetKey(m_opWindow, GLFW_KEY_DOWN ) == GLFW_PRESS){
        pos -= cameraSpeed * cameraFront;
    }
// Strafe right
    if (glfwGetKey( m_opWindow, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        pos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    }
// Strafe left`
    if (glfwGetKey(m_opWindow,  GLFW_KEY_LEFT ) == GLFW_PRESS){
        pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    setPos(glm::vec4(pos, 1.0f));
}