#pragma once

#include <memory>
#include <string>

// Forward declarations
class Window;
class Camera;
class ECS;
class VulkanContext;

/**
 * @brief 主应用程序类 - 已为你实现
 *
 * 这个类是应用程序的核心，负责：
 * - 初始化所有系统（窗口、Vulkan、ECS等）
 * - 主循环管理
 * - 事件处理
 *
 * 你不需要修改这个类。
 * 只需要在 main.cpp 中创建实例并调用 run()。
 */
class Application {
public:
    struct Config {
        int windowWidth = 1280;
        int windowHeight = 720;
        std::string windowTitle = "Vulkan Sandbox";
        bool enableValidation = true;
    };

    Application(const Config& config);
    ~Application();

    // 禁止拷贝
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // 主循环
    void run();

    // Getters
    Window* getWindow() const { return m_window.get(); }
    Camera* getCamera() const { return m_camera.get(); }
    ECS* getECS() const { return m_ecs.get(); }
    VulkanContext* getVulkanContext() const { return m_vulkanContext.get(); }

private:
    void initialize();
    void cleanup();

    void setupInputCallbacks();
    void update(float deltaTime);
    void render();

    void onWindowResize(int width, int height);
    void onKey(int key, int scancode, int action, int mods);
    void onMouseButton(int button, int action, int mods);
    void onMouseMove(double xpos, double ypos);
    void onScroll(double xoffset, double yoffset);

    Config m_config;

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<ECS> m_ecs;
    std::unique_ptr<VulkanContext> m_vulkanContext;

    // 时间管理
    float m_lastFrameTime = 0.0f;
    float m_deltaTime = 0.0f;

    bool m_initialized = false;
};
