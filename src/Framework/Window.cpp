#include "Framework/Window.h"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Tell GLFW not to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Store this pointer in GLFW window for callbacks
    glfwSetWindowUserPointer(m_window, this);

    // Setup callbacks
    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, cursorPosCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

    std::cout << "Window created: " << width << "x" << height << std::endl;
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::waitEvents() {
    glfwWaitEvents();
}

void Window::setMouseCaptured(bool captured) {
    m_mouseCaptured = captured;
    glfwSetInputMode(m_window, GLFW_CURSOR,
        captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

// Static callbacks
void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->m_width = width;
    win->m_height = height;

    if (win->m_resizeCallback) {
        win->m_resizeCallback(width, height);
    }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (win->m_keyCallback) {
        win->m_keyCallback(key, scancode, action, mods);
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (win->m_mouseButtonCallback) {
        win->m_mouseButtonCallback(button, action, mods);
    }
}

void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (win->m_mouseMoveCallback) {
        win->m_mouseMoveCallback(xpos, ypos);
    }
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (win->m_scrollCallback) {
        win->m_scrollCallback(xoffset, yoffset);
    }
}
