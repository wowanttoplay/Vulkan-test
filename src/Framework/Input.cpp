#include "Framework/Input.h"

// 静态成员初始化
std::unordered_map<int, bool> Input::s_keyStates;
std::unordered_map<int, bool> Input::s_mouseButtonStates;
double Input::s_mouseX = 0.0;
double Input::s_mouseY = 0.0;
double Input::s_lastMouseX = 0.0;
double Input::s_lastMouseY = 0.0;
double Input::s_mouseDeltaX = 0.0;
double Input::s_mouseDeltaY = 0.0;
bool Input::s_firstMouse = true;

bool Input::isKeyPressed(int key) {
    auto it = s_keyStates.find(key);
    return it != s_keyStates.end() && it->second;
}

bool Input::isKeyReleased(int key) {
    return !isKeyPressed(key);
}

bool Input::isMouseButtonPressed(int button) {
    auto it = s_mouseButtonStates.find(button);
    return it != s_mouseButtonStates.end() && it->second;
}

bool Input::isMouseButtonReleased(int button) {
    return !isMouseButtonPressed(button);
}

void Input::getMousePosition(double& x, double& y) {
    x = s_mouseX;
    y = s_mouseY;
}

void Input::getMouseDelta(double& dx, double& dy) {
    dx = s_mouseDeltaX;
    dy = s_mouseDeltaY;
}

void Input::setKeyState(int key, bool pressed) {
    s_keyStates[key] = pressed;
}

void Input::setMouseButtonState(int button, bool pressed) {
    s_mouseButtonStates[button] = pressed;
}

void Input::setMousePosition(double x, double y) {
    if (s_firstMouse) {
        s_lastMouseX = x;
        s_lastMouseY = y;
        s_firstMouse = false;
    }

    s_mouseDeltaX = x - s_lastMouseX;
    s_mouseDeltaY = s_lastMouseY - y;  // Y坐标反转

    s_lastMouseX = x;
    s_lastMouseY = y;

    s_mouseX = x;
    s_mouseY = y;
}

void Input::update() {
    // 每帧重置delta（如果没有新的鼠标移动事件）
    // 这会在下一次setMousePosition时更新
}
