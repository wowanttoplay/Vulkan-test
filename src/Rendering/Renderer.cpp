#include "Rendering/Renderer.h"
#include "Rendering/ForwardPass.h"
#include "Core/VulkanContext.h"
#include "Core/VulkanSwapchain.h"
#include "Framework/Camera.h"
#include "ECS/ECS.h"
#include <stdexcept>
#include <array>

Renderer::~Renderer() {
    cleanup();
}

void Renderer::initialize(VulkanContext* context, Camera* camera) {
    m_context = context;
    m_camera = camera;

    // TODO: 实现这些初始化函数
    createRenderPass();
    createDepthResources();
    createFramebuffers();
    createCommandPool();
    createCommandBuffers();
    createSyncObjects();

    // 初始化渲染Pass
    initializeRenderPasses();
}

void Renderer::cleanup() {
    VkDevice device = m_context->getDevice();

    // 等待设备空闲
    vkDeviceWaitIdle(device);

    // 清理渲染Pass
    for (auto& pass : m_renderPasses) {
        pass->cleanup();
    }
    m_renderPasses.clear();

    // 清理同步对象
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device, m_imageAvailableSemaphores[i], nullptr);
        vkDestroySemaphore(device, m_renderFinishedSemaphores[i], nullptr);
        vkDestroyFence(device, m_inFlightFences[i], nullptr);
    }

    // 清理Command Pool（会自动释放Command Buffers）
    if (m_commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device, m_commandPool, nullptr);
    }

    // 清理Framebuffers
    for (auto framebuffer : m_framebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    // 清理深度缓冲
    if (m_depthImageView != VK_NULL_HANDLE) {
        vkDestroyImageView(device, m_depthImageView, nullptr);
    }
    if (m_depthImage != VK_NULL_HANDLE) {
        vkDestroyImage(device, m_depthImage, nullptr);
    }
    if (m_depthImageMemory != VK_NULL_HANDLE) {
        vkFreeMemory(device, m_depthImageMemory, nullptr);
    }

    // 清理Render Pass
    if (m_renderPass != VK_NULL_HANDLE) {
        vkDestroyRenderPass(device, m_renderPass, nullptr);
    }
}

void Renderer::render(ECS& ecs) {
    VkDevice device = m_context->getDevice();

    // 等待上一帧完成
    vkWaitForFences(device, 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);

    // 获取下一个交换链图像
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(
        device,
        m_context->getSwapchain()->getHandle(),
        UINT64_MAX,
        m_imageAvailableSemaphores[m_currentFrame],
        VK_NULL_HANDLE,
        &imageIndex
    );

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateFramebuffers();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }

    // 重置fence（等待新的帧）
    vkResetFences(device, 1, &m_inFlightFences[m_currentFrame]);

    // 重置并记录命令缓冲区
    VkCommandBuffer cmd = m_commandBuffers[m_currentFrame];
    vkResetCommandBuffer(cmd, 0);
    recordCommandBuffer(cmd, imageIndex, ecs);

    // 提交命令缓冲区
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphores[m_currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmd;

    VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphores[m_currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(m_context->getGraphicsQueue(), 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer!");
    }

    // 呈现
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { m_context->getSwapchain()->getHandle() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(m_context->getPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        recreateFramebuffers();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swap chain image!");
    }

    // 切换到下一帧
    m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Renderer::recreateFramebuffers() {
    VkDevice device = m_context->getDevice();

    // 等待设备空闲
    vkDeviceWaitIdle(device);

    // 清理旧的framebuffers
    for (auto framebuffer : m_framebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
    m_framebuffers.clear();

    // 重建
    createFramebuffers();
}

// ============================================================================
// [TODO] 实现这些Vulkan函数
// ============================================================================

void Renderer::createRenderPass() {
    // TODO: 创建Vulkan RenderPass
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Render_passes
    throw std::runtime_error("createRenderPass() not implemented yet!");
}

void Renderer::createDepthResources() {
    // TODO: 创建深度缓冲
    // 参考: https://vulkan-tutorial.com/Depth_buffering
    throw std::runtime_error("createDepthResources() not implemented yet!");
}

void Renderer::createFramebuffers() {
    // TODO: 创建Framebuffers
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Framebuffers
    throw std::runtime_error("createFramebuffers() not implemented yet!");
}

void Renderer::createCommandPool() {
    // TODO: 创建Command Pool
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Command_buffers
    throw std::runtime_error("createCommandPool() not implemented yet!");
}

void Renderer::createCommandBuffers() {
    // TODO: 创建Command Buffers
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Command_buffers
    throw std::runtime_error("createCommandBuffers() not implemented yet!");
}

void Renderer::createSyncObjects() {
    // TODO: 创建同步对象（Semaphores和Fences）
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Rendering_and_presentation
    throw std::runtime_error("createSyncObjects() not implemented yet!");
}

void Renderer::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, ECS& ecs) {
    // TODO: 记录命令缓冲区
    // 1. vkBeginCommandBuffer
    // 2. vkCmdBeginRenderPass
    // 3. 执行各个渲染Pass
    // 4. vkCmdEndRenderPass
    // 5. vkEndCommandBuffer
    //
    // 参考: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Command_buffers
    throw std::runtime_error("recordCommandBuffer() not implemented yet!");
}

void Renderer::initializeRenderPasses() {
    // 创建ForwardPass
    auto forwardPass = std::make_unique<ForwardPass>();
    forwardPass->initialize(m_context->getDevice(), m_renderPass, m_context->getSwapchain()->getExtent());
    forwardPass->setCamera(m_camera);
    m_renderPasses.push_back(std::move(forwardPass));

    // Later: 添加更多Pass
    // m_renderPasses.push_back(std::make_unique<ShadowPass>(...));
    // m_renderPasses.push_back(std::make_unique<PostProcessPass>(...));
}
