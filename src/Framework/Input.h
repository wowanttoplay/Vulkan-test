#pragma once

#include <unordered_map>

/**
 * @brief 输入管理器 - 已为你实现
 *
 * 这个类提供：
 * - 键盘状态查询
 * - 鼠标按钮状态查询
 * - 鼠标位置追踪
 *
 * 使用方法：
 * if (Input::isKeyPressed(GLFW_KEY_W)) { ... }
 * if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) { ... }
 */
class Input {
public:
    // 键盘
    static bool isKeyPressed(int key);
    static bool isKeyReleased(int key);

    // 鼠标按钮
    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonReleased(int button);

    // 鼠标位置
    static void getMousePosition(double& x, double& y);
    static void getMouseDelta(double& dx, double& dy);

    // 内部使用（由Window调用）
    static void setKeyState(int key, bool pressed);
    static void setMouseButtonState(int button, bool pressed);
    static void setMousePosition(double x, double y);
    static void update();  // 每帧调用，更新delta等

private:
    static std::unordered_map<int, bool> s_keyStates;
    static std::unordered_map<int, bool> s_mouseButtonStates;
    static double s_mouseX, s_mouseY;
    static double s_lastMouseX, s_lastMouseY;
    static double s_mouseDeltaX, s_mouseDeltaY;
    static bool s_firstMouse;
};
