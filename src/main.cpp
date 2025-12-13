#include "Framework/Application.h"
#include <iostream>
#include <stdexcept>

/**
 * @brief 程序入口
 *
 * ========================================================================
 * VULKAN LEARNING PROJECT - PHASE 1
 * ========================================================================
 *
 * 目标：
 * - 渲染一个旋转的彩色立方体
 * - 学习Vulkan基础（Instance, Device, Swapchain, Pipeline等）
 *
 * 你的任务：
 * 1. 实现 VulkanContext.h 中的5个TODO
 * 2. 实现 VulkanSwapchain.h 中的TODO
 * 3. 实现 VulkanPipeline.h 中的TODO
 * 4. 实现 VulkanBuffer.h 中的TODO
 * 5. 实现 VulkanImage.h 中的TODO（可选，Phase 2需要）
 * 6. 实现 Renderer.cpp 中的TODO
 *
 * 学习资源：
 * - Vulkan Tutorial: https://vulkan-tutorial.com/
 * - Phase 1 Guide: docs/PHASE1_GUIDE.md
 *
 * 控制：
 * - WASD：移动相机
 * - 鼠标：右键捕获，移动视角
 * - E/Space：向上移动
 * - Q/Shift：向下移动
 * - ESC：退出
 *
 * ========================================================================
 */

int main() {
    try {
        // 配置应用程序
        Application::Config config;
        config.windowWidth = 1280;
        config.windowHeight = 720;
        config.windowTitle = "Vulkan Learning - Phase 1";
        config.enableValidation = true;  // 开启验证层（调试用）

        // 创建并运行应用程序
        Application app(config);
        app.run();

    } catch (const std::exception& e) {
        std::cerr << "\n========================================" << std::endl;
        std::cerr << "FATAL ERROR:" << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << "========================================\n" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
