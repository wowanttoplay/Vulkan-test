#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

class VulkanContext;
class ECS;
class Camera;
class IRenderPass;

/**
 * @brief 渲染器 - 协调所有渲染操作
 *
 * 职责：
 * - 管理Render Pass（Vulkan的渲染通道）
 * - 管理Framebuffers
 * - 管理Command Buffers
 * - 协调渲染Pass的执行
 * - 处理帧同步（信号量、栅栏）
 *
 * 渲染流程：
 * 1. acquireNextImage() - 获取下一个交换链图像
 * 2. beginFrame() - 开始记录命令
 * 3. beginRenderPass() - 开始Vulkan RenderPass
 * 4. 执行各个渲染Pass（ForwardPass, ShadowPass等）
 * 5. endRenderPass() - 结束Vulkan RenderPass
 * 6. endFrame() - 结束记录
 * 7. submitAndPresent() - 提交GPU并呈现
 */
class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    void initialize(VulkanContext* context, Camera* camera);
    void cleanup();

    // 渲染主函数
    void render(ECS& ecs);

    // Framebuffer调整大小（窗口resize时调用）
    void recreateFramebuffers();

private:
    // ========================================================================
    // [YOUR VULKAN LEARNING TASK] 实现这些函数
    // ========================================================================
    // 这些是你需要实现的Vulkan渲染功能

    /**
     * @brief 创建Vulkan Render Pass
     *
     * CONCEPT: RenderPass定义渲染目标和操作
     * - Attachments：颜色、深度等附件
     * - Subpasses：渲染子通道
     * - Dependencies：子通道之间的依赖
     *
     * Phase 1需要：
     * - 1个颜色附件（交换链图像）
     * - 1个深度附件
     * - 1个subpass
     */
    void createRenderPass();

    /**
     * @brief 创建深度缓冲
     *
     * CONCEPT: 深度测试需要深度缓冲
     * - 格式：VK_FORMAT_D32_SFLOAT或VK_FORMAT_D24_UNORM_S8_UINT
     * - 使用VulkanImage创建
     */
    void createDepthResources();

    /**
     * @brief 创建Framebuffers
     *
     * CONCEPT: Framebuffer是RenderPass的具体实例
     * - 为每个交换链图像创建一个Framebuffer
     * - 包含颜色附件（交换链ImageView）和深度附件
     */
    void createFramebuffers();

    /**
     * @brief 创建Command Pool
     *
     * CONCEPT: CommandPool管理CommandBuffer的内存
     * - 每个线程应该有自己的CommandPool
     * - Phase 1只需要一个
     */
    void createCommandPool();

    /**
     * @brief 创建Command Buffers
     *
     * CONCEPT: CommandBuffer记录GPU命令
     * - 为每个交换链图像创建一个CommandBuffer
     * - 可以预先记录，也可以每帧重新记录
     */
    void createCommandBuffers();

    /**
     * @brief 创建同步对象（信号量、栅栏）
     *
     * CONCEPT: GPU/CPU同步
     * - Semaphore：GPU-GPU同步（图像可用、渲染完成）
     * - Fence：CPU-GPU同步（等待帧完成）
     */
    void createSyncObjects();

    /**
     * @brief 记录命令缓冲区
     *
     * CONCEPT: 将渲染命令记录到CommandBuffer
     * - beginRenderPass
     * - 执行各个渲染Pass
     * - endRenderPass
     */
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, ECS& ecs);

    // 渲染Pass管理
    void initializeRenderPasses();

    // 外部引用
    VulkanContext* m_context = nullptr;
    Camera* m_camera = nullptr;

    // Vulkan对象
    VkRenderPass m_renderPass = VK_NULL_HANDLE;
    VkCommandPool m_commandPool = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> m_framebuffers;
    std::vector<VkCommandBuffer> m_commandBuffers;

    // 深度缓冲
    VkImage m_depthImage = VK_NULL_HANDLE;
    VkDeviceMemory m_depthImageMemory = VK_NULL_HANDLE;
    VkImageView m_depthImageView = VK_NULL_HANDLE;

    // 同步对象（每帧）
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    uint32_t m_currentFrame = 0;

    // 渲染Pass列表（可扩展）
    std::vector<std::unique_ptr<IRenderPass>> m_renderPasses;
};
