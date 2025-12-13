#include "Framework/Camera.h"
#include <GLFW/glfw3.h>
#include <algorithm>

Camera::Camera(Type type) : m_type(type) {
    updateCameraVectors();
}

void Camera::update(float deltaTime) {
    // 处理移动（基于当前按键状态）
    float velocity = moveSpeed * deltaTime;

    if (m_keys[GLFW_KEY_W]) {
        m_position += m_front * velocity;
    }
    if (m_keys[GLFW_KEY_S]) {
        m_position -= m_front * velocity;
    }
    if (m_keys[GLFW_KEY_A]) {
        m_position -= m_right * velocity;
    }
    if (m_keys[GLFW_KEY_D]) {
        m_position += m_right * velocity;
    }
    if (m_keys[GLFW_KEY_E] || m_keys[GLFW_KEY_SPACE]) {
        m_position += m_worldUp * velocity;
    }
    if (m_keys[GLFW_KEY_Q] || m_keys[GLFW_KEY_LEFT_SHIFT]) {
        m_position -= m_worldUp * velocity;
    }
}

void Camera::processKeyboard(int key, float deltaTime) {
    if (key >= 0 && key < 1024) {
        m_keys[key] = true;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // 限制俯仰角，避免翻转
    m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    m_fov -= yoffset * zoomSpeed;
    m_fov = std::clamp(m_fov, 1.0f, 90.0f);
}

void Camera::setRotation(float pitch, float yaw) {
    m_pitch = pitch;
    m_yaw = yaw;
    updateCameraVectors();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    m_fov = fov;
    m_aspect = aspect;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    glm::mat4 proj = glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane);

    // Vulkan的Y坐标是反的（与OpenGL相比）
    proj[1][1] *= -1;

    return proj;
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::updateCameraVectors() {
    // 根据欧拉角计算前向向量
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // 重新计算右向量和上向量
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
