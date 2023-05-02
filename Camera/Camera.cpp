//
// Created by Theodora Vraimakis on 11/02/2023.
//

#include "Camera.h"

Camera::Camera
        (
                GLFWwindow* window,
                glm::vec4& pos,
                glm::vec4& target,
                const float FOV,
                const float ratio
        ) : m_window(window),
            m_FOV(FOV),
            m_ratio(ratio),
            m_pos(pos),
            m_objectPos(target)
{
    m_rightVec = glm::vec3(0.0f, 1.0f, 0.0f);
    m_proj = getNewProjMat(
            glm::radians(m_FOV),
            m_ratio
    );

    m_prevCursor = glm::vec2(0.0f);
    m_currentCursor = glm::vec2(0.0f);
}

Camera::~Camera() = default;

const glm::mat4& Camera
::getProjectionM() const
{
    return m_proj;
}

const glm::mat4& Camera
::getViewMat()
{
    m_view = glm::lookAt(
            glm::vec3(m_pos),
            glm::vec3(m_objectPos),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );

    return m_view;
}

const float& Camera
::getFOV() const
{
    return m_FOV;
}

glm::mat4 Camera::getNewProjMat(
        const float newFOV,
        const float newRatio
) {

    glm::mat4 proj = glm::perspective(
            newFOV,
            newRatio, 0.1f, 100.0f
    );
    return proj;
}

void Camera
::setFOV(const float& newFOV)
{
    m_FOV = newFOV;

    m_proj = getNewProjMat(glm::radians(newFOV),
                           m_ratio
    );
}

void Camera
::setPos(const glm::vec4& pos)
{
    m_pos = pos;
}

void Camera
::setObjectPos(const glm::vec4& objectPos)
{
    m_objectPos = objectPos;
}

glm::vec4& Camera
::getPos()
{
    return m_pos;
}

glm::vec4& Camera
::getObjectPos()
{
    return m_objectPos;
}
// taken from tutorial: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
glm::vec3 Camera::getArcballVec(const float x, float y)
{
    glm::vec3 point = glm::vec3(
            1.0f * x / (float)Config::SCR_WIDTH * 2.0f - 1.0f,
            -1.0f * (1.0f * y / (float)Config::SCR_HEIGHT * 2.0f - 1.0f),
            0.0f
    );

    float distanceSquared = point.x * point.x + point.y * point.y;

    if (distanceSquared <= 1.0f)
        point.z = glm::sqrt(1.0f - distanceSquared);
    else
        point = glm::normalize(point);

    return point;
}

void Camera::updateViewMat() {
    m_view = glm::lookAt(
            glm::vec3(m_pos),
            glm::vec3(m_objectPos),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

void Camera::update() {
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    glm::vec3 from = getArcballVec(m_prevCursor.x, m_prevCursor.y);
    glm::vec3 to = getArcballVec(x, y);

    if (glm::length(from) < std::numeric_limits<float>::epsilon() || glm::length(to) < std::numeric_limits<float>::epsilon())
        return;

    float dotProduct = glm::dot(from, to);
    float angle = glm::acos(glm::min(1.0f, dotProduct));

    if (std::isnan(angle) || std::isinf(angle))
        return;

    glm::vec3 rotationAxis = glm::cross(from, to);
    if (glm::length(rotationAxis) < std::numeric_limits<float>::epsilon())
        return;

    glm::quat quat = glm::quat_cast(glm::rotate(glm::mat4(1.0f), angle, rotationAxis));

    if (glm::any(glm::isnan(quat))) {
        return;
    }

    glm::mat4 rotationMat = glm::mat4_cast(quat);
    m_pos = glm::inverse(rotationMat) * glm::vec4(m_pos - m_objectPos) + glm::vec4(m_objectPos);

    updateViewMat();

    m_prevCursor.x = x;
    m_prevCursor.y = y;
}


void Camera::saveCursor()
{
    double x, y;

    glfwGetCursorPos(m_window, &x, &y);

    m_currentCursor = m_prevCursor = glm::vec2(x, y);
}
