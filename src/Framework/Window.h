#pragma once

#include <string>
#include <functional>

// Forward declare GLFW types to avoid including GLFW in header
struct GLFWwindow;

/**
 * @brief Window管理类 - 封装GLFW窗口
 *
 * 这个类已经为你实现好了，你不需要修改它。
 * 它处理：
 * - 窗口创建和销毁
 * - 窗口事件（resize, close等）
 * - 输入回调设置
 */
class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    // 禁止拷贝
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Window operations
    void pollEvents();
    bool shouldClose() const;
    void waitEvents();

    // Getters
    GLFWwindow* getHandle() const { return m_window; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    bool isMinimized() const { return m_width == 0 || m_height == 0; }

    // Callbacks
    using ResizeCallback = std::function<void(int, int)>;
    using KeyCallback = std::function<void(int, int, int, int)>;
    using MouseButtonCallback = std::function<void(int, int, int)>;
    using MouseMoveCallback = std::function<void(double, double)>;
    using ScrollCallback = std::function<void(double, double)>;

    void setResizeCallback(ResizeCallback callback) { m_resizeCallback = callback; }
    void setKeyCallback(KeyCallback callback) { m_keyCallback = callback; }
    void setMouseButtonCallback(MouseButtonCallback callback) { m_mouseButtonCallback = callback; }
    void setMouseMoveCallback(MouseMoveCallback callback) { m_mouseMoveCallback = callback; }
    void setScrollCallback(ScrollCallback callback) { m_scrollCallback = callback; }

    // Mouse control
    void setMouseCaptured(bool captured);
    bool isMouseCaptured() const { return m_mouseCaptured; }

private:
    // GLFW callbacks (静态函数)
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    std::string m_title;

    bool m_mouseCaptured = false;

    // User callbacks
    ResizeCallback m_resizeCallback;
    KeyCallback m_keyCallback;
    MouseButtonCallback m_mouseButtonCallback;
    MouseMoveCallback m_mouseMoveCallback;
    ScrollCallback m_scrollCallback;
};
