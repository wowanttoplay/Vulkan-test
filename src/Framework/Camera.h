#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief FPS风格相机 - 已为你实现
 *
 * 这个相机类提供：
 * - WASD移动
 * - 鼠标旋转
 * - 可配置的移动速度和灵敏度
 * - View和Projection矩阵计算
 *
 * 你不需要修改这个类，直接使用即可。
 */
class Camera {
public:
    enum class Type {
        FirstPerson,  // FPS相机
        Orbit         // 轨道相机（绕目标旋转，Phase 3会实现）
    };

    Camera(Type type = Type::FirstPerson);

    // 更新相机（每帧调用）
    void update(float deltaTime);

    // 输入处理
    void processKeyboard(int key, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);

    // 设置
    void setPosition(const glm::vec3& position) { m_position = position; }
    void setRotation(float pitch, float yaw);
    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);

    // 获取矩阵
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;

    // 获取属性
    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getForward() const { return m_front; }
    glm::vec3 getRight() const { return m_right; }
    glm::vec3 getUp() const { return m_up; }

    float getPitch() const { return m_pitch; }
    float getYaw() const { return m_yaw; }

    // 配置
    float moveSpeed = 5.0f;
    float mouseSensitivity = 0.1f;
    float zoomSpeed = 1.0f;

private:
    void updateCameraVectors();

    Type m_type;

    // 相机位置和方向
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // 欧拉角
    float m_pitch = 0.0f;  // 俯仰角
    float m_yaw = -90.0f;  // 偏航角

    // 投影参数
    float m_fov = 45.0f;
    float m_aspect = 16.0f / 9.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 100.0f;

    // 键盘状态（用于平滑移动）
    bool m_keys[1024] = {false};
};
