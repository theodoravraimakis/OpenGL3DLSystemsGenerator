//
// Created by Theodora Vraimakis on 11/02/2023.
//

#include "ArcballCamera.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"

ArcballCamera::ArcballCamera
(
        GLFWwindow* window,
        const glm::vec4 pos,
        const glm::vec4 target,
        const float FOV
) : m_opWindow(window),
    m_FOV(FOV),
    m_pos(pos),
    m_targetPos(target)
{
    m_view = glm::lookAt(
            // Eyes position.
            glm::vec3(m_pos),
            // Center position
            glm::vec3(0.0f, 0.0f, 0.0f),
            // Up axis
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
    m_proj = getUpdatedProjMatrix(
            glm::radians(m_FOV)
    );
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
    m_view = glm::lookAt(
            // Eyes position.
            glm::vec3(m_pos),
            // Center position
            glm::vec3(m_targetPos),
            // Up axis
            glm::vec3(0.0f, 1.0f, 0.0f)
//    glm::vec4(1.0f, 0.0f, 0.0f)
    );

    return m_view;
}

const float& ArcballCamera
::getFOV() const
{
    return m_FOV;
}

glm::mat4 ArcballCamera::getUpdatedProjMatrix(
        const float newFOV
) {
    glm::mat4 proj = glm::perspective(
            newFOV,
            (float)Config::SCR_WIDTH / (float)Config::SCR_HEIGHT, 0.1f, 100.0f
    );

    // GLM was designed for OpenGl, where the Y coordinate of the clip coord. is
    // inverted. To compensate for that, we have to flip the sign on the scaling
    // factor of the Y axis.
    proj[1][1] *= -1;

    return proj;
}

void ArcballCamera
::setFOV(const float newFOV)
{
    m_FOV = newFOV;

    m_proj = getUpdatedProjMatrix(glm::radians(newFOV));
}

void ArcballCamera
::setPos(const glm::vec4 pos)
{
    m_pos = pos;
}

void ArcballCamera
::setTargetPos(const glm::vec4 targetPos)
{
    m_targetPos = targetPos;
}

glm::vec4 ArcballCamera
::getPos() const
{
    return m_pos;
}

glm::vec4 ArcballCamera
::getTargetPos() const
{
    return m_targetPos;
}

glm::vec3 ArcballCamera::getArcballVector(const float x, const float y)
{
    glm::vec3 P = glm::vec3(
            1.0f * x / Config::SCR_WIDTH * 2.0f - 1.0f,
            -1.0f * (1.0f * y / Config::SCR_HEIGHT * 2.0f - 1.0f),
            0.0f
    );

    float OPsquared = P.x * P.x + P.y * P.y;

    if (OPsquared <= 1.0)
    {
        // Pythagoras
        P.z = glm::sqrt(1 - OPsquared);
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
void ArcballCamera::updateCameraPos(glm::mat4& newRot)
{
    double x, y;
    glfwGetCursorPos(m_opWindow, &x, &y);

    m_currentCursorPos = glm::vec2(x, y);

    if (x != m_lastCursorPos.x || y != m_lastCursorPos.y)
    {
        glm::vec3 v1 = getArcballVector(m_lastCursorPos.x, m_lastCursorPos.y);
        glm::vec3 v2 = getArcballVector(x, y);

        float angle = glm::acos(glm::min(1.0f, glm::dot(v1, v2))) * 0.02;

        glm::vec3 axisInCameraCoord = glm::cross(v1, v2);
        glm::mat3 camera2object = glm::inverse(
                glm::mat3(m_view) * glm::mat3(newRot)
        );
        glm::vec3 axisInObjectCoord = camera2object * axisInCameraCoord;

        newRot = glm::rotate(
                newRot,
                glm::degrees(angle),
                axisInObjectCoord
        );

        m_lastCursorPos = m_currentCursorPos;

        m_pos = newRot * m_pos;
//        m_view = newRot;

    }
}

void ArcballCamera::saveCursorPos()
{
    double x, y;

    glfwGetCursorPos(m_opWindow, &x, &y);

    m_currentCursorPos = m_lastCursorPos = glm::vec2(x, y);
}