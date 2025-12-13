#include "Framework/Application.h"
#include "Framework/Window.h"
#include "Framework/Camera.h"
#include "Framework/Input.h"
#include "ECS/ECS.h"
#include "Core/VulkanContext.h"
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application(const Config& config)
    : m_config(config) {
}

Application::~Application() {
    cleanup();
}

void Application::run() {
    initialize();

    std::cout << "\n========================================" << std::endl;
    std::cout << "Application started!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  WASD - Move camera" << std::endl;
    std::cout << "  Mouse - Look around (right-click to capture)" << std::endl;
    std::cout << "  E/Space - Move up" << std::endl;
    std::cout << "  Q/Shift - Move down" << std::endl;
    std::cout << "  ESC - Exit" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // 主循环
    while (!m_window->shouldClose()) {
        // 计算deltaTime
        float currentTime = static_cast<float>(glfwGetTime());
        m_deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        // 处理输入
        m_window->pollEvents();
        Input::update();

        // 更新
        update(m_deltaTime);

        // 渲染
        render();
    }

    std::cout << "Application shutting down..." << std::endl;
}

void Application::initialize() {
    if (m_initialized) return;

    std::cout << "Initializing application..." << std::endl;

    // 1. 创建窗口
    std::cout << "Creating window..." << std::endl;
    m_window = std::make_unique<Window>(
        m_config.windowWidth,
        m_config.windowHeight,
        m_config.windowTitle
    );

    // 2. 设置输入回调
    setupInputCallbacks();

    // 3. 创建相机
    std::cout << "Creating camera..." << std::endl;
    m_camera = std::make_unique<Camera>();
    m_camera->setPerspective(
        45.0f,
        static_cast<float>(m_config.windowWidth) / m_config.windowHeight,
        0.1f,
        100.0f
    );
    m_camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    // 4. 创建ECS
    std::cout << "Creating ECS..." << std::endl;
    m_ecs = std::make_unique<ECS>();

    // 5. 初始化Vulkan（你需要实现这部分）
    std::cout << "\n========================================" << std::endl;
    std::cout << "Initializing Vulkan..." << std::endl;
    std::cout << "========================================" << std::endl;
    m_vulkanContext = std::make_unique<VulkanContext>();

    try {
        m_vulkanContext->initialize(m_window.get(), m_config.enableValidation);
        std::cout << "Vulkan initialized successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialize Vulkan: " << e.what() << std::endl;
        throw;
    }

    m_initialized = true;
    std::cout << "Application initialized successfully!" << std::endl;
}

void Application::cleanup() {
    if (!m_initialized) return;

    // 清理顺序很重要！
    // Vulkan需要先清理（在ECS之前）
    if (m_vulkanContext) {
        m_vulkanContext->cleanup();
        m_vulkanContext.reset();
    }

    m_ecs.reset();
    m_camera.reset();
    m_window.reset();

    m_initialized = false;
}

void Application::setupInputCallbacks() {
    // 窗口resize回调
    m_window->setResizeCallback([this](int w, int h) {
        onWindowResize(w, h);
    });

    // 键盘回调
    m_window->setKeyCallback([this](int key, int scancode, int action, int mods) {
        onKey(key, scancode, action, mods);
    });

    // 鼠标按钮回调
    m_window->setMouseButtonCallback([this](int button, int action, int mods) {
        onMouseButton(button, action, mods);
    });

    // 鼠标移动回调
    m_window->setMouseMoveCallback([this](double x, double y) {
        onMouseMove(x, y);
    });

    // 滚轮回调
    m_window->setScrollCallback([this](double xoffset, double yoffset) {
        onScroll(xoffset, yoffset);
    });
}

void Application::update(float deltaTime) {
    // 更新相机
    m_camera->update(deltaTime);

    // TODO: 更新ECS系统
    // TODO: 更新物理、动画等
}

void Application::render() {
    // TODO: Vulkan渲染
    // 这会在你实现了VulkanSwapchain和渲染管线后完成

    // 目前只是一个占位符
    // std::cout << "Rendering frame..." << std::endl;
}

void Application::onWindowResize(int width, int height) {
    std::cout << "Window resized: " << width << "x" << height << std::endl;

    // 更新相机aspect ratio
    m_camera->setPerspective(
        45.0f,
        static_cast<float>(width) / height,
        0.1f,
        100.0f
    );

    // TODO: 重建Vulkan swapchain
}

void Application::onKey(int key, int scancode, int action, int mods) {
    // 更新Input状态
    if (action == GLFW_PRESS) {
        Input::setKeyState(key, true);
    } else if (action == GLFW_RELEASE) {
        Input::setKeyState(key, false);
    }

    // 特殊键处理
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // ESC退出
        glfwSetWindowShouldClose(m_window->getHandle(), true);
    }

    // 处理相机输入
    if (action != GLFW_RELEASE) {
        m_camera->processKeyboard(key, m_deltaTime);
    }
}

void Application::onMouseButton(int button, int action, int mods) {
    // 更新Input状态
    Input::setMouseButtonState(button, action == GLFW_PRESS);

    // 右键捕获鼠标
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            m_window->setMouseCaptured(true);
        } else if (action == GLFW_RELEASE) {
            m_window->setMouseCaptured(false);
        }
    }

    // TODO: 左键用于对象拾取（Phase 2）
}

void Application::onMouseMove(double xpos, double ypos) {
    // 更新Input状态
    Input::setMousePosition(xpos, ypos);

    // 如果鼠标被捕获，处理相机旋转
    if (m_window->isMouseCaptured()) {
        double dx, dy;
        Input::getMouseDelta(dx, dy);
        m_camera->processMouseMovement(static_cast<float>(dx), static_cast<float>(dy));
    }
}

void Application::onScroll(double xoffset, double yoffset) {
    m_camera->processMouseScroll(static_cast<float>(yoffset));
}
