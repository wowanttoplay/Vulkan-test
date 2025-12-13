#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

class Window;

/**
 * @brief Vulkan交换链管理
 *
 * ========================================================================
 * [学习模块 2] VULKAN SWAPCHAIN
 * ========================================================================
 *
 * SWAPCHAIN是什么？
 * - 交换链是一系列用于呈现到屏幕的图像（帧缓冲）
 * - 类似于"双缓冲"或"三缓冲"的概念
 * - 你渲染到一个图像，同时显示另一个图像
 *
 * 为什么需要SWAPCHAIN？
 * - Vulkan不能直接渲染到屏幕
 * - 需要一个图像队列来管理呈现
 * - 避免画面撕裂（tearing）
 *
 * SWAPCHAIN包含什么？
 * - VkSwapchainKHR：交换链本身
 * - VkImage[]：一系列图像（通常2-3个）
 * - VkImageView[]：图像视图（用于访问图像）
 * - VkFramebuffer[]：帧缓冲（稍后创建）
 *
 * 关键概念：
 * - Present Mode：呈现模式（FIFO, Mailbox, Immediate）
 * - Surface Format：表面格式（颜色空间）
 * - Extent：交换链图像的分辨率
 *
 * 你需要实现：
 * 1. querySwapchainSupport() - 查询支持的功能
 * 2. chooseSwapSurfaceFormat() - 选择颜色格式
 * 3. chooseSwapPresentMode() - 选择呈现模式
 * 4. chooseSwapExtent() - 选择分辨率
 * 5. createSwapchain() - 创建交换链
 * 6. createImageViews() - 创建图像视图
 * 7. recreate() - 窗口调整大小时重建
 */
class VulkanSwapchain {
public:
    VulkanSwapchain() = default;
    ~VulkanSwapchain();

    void initialize(
        VkPhysicalDevice physicalDevice,
        VkDevice device,
        VkSurfaceKHR surface,
        Window* window
    );

    void cleanup();
    void recreate();

    // Getters
    VkSwapchainKHR getHandle() const { return m_swapchain; }
    VkFormat getImageFormat() const { return m_imageFormat; }
    VkExtent2D getExtent() const { return m_extent; }
    const std::vector<VkImage>& getImages() const { return m_images; }
    const std::vector<VkImageView>& getImageViews() const { return m_imageViews; }
    uint32_t getImageCount() const { return static_cast<uint32_t>(m_images.size()); }

    // ========================================================================
    // [TODO 1] 查询交换链支持的功能
    // ========================================================================
    // CONCEPT: 不是所有GPU都支持所有功能，需要查询
    //
    // SwapchainSupportDetails包含：
    // - VkSurfaceCapabilitiesKHR：基本能力（min/max图像数量，分辨率等）
    // - VkSurfaceFormatKHR[]：支持的格式（RGBA8, BGRA8等）
    // - VkPresentModeKHR[]：支持的呈现模式（FIFO, Mailbox等）
    //
    // YOU NEED TO:
    // 1. 调用 vkGetPhysicalDeviceSurfaceCapabilitiesKHR() 获取capabilities
    // 2. 调用 vkGetPhysicalDeviceSurfaceFormatsKHR() 获取formats
    // 3. 调用 vkGetPhysicalDeviceSurfacePresentModesKHR() 获取presentModes
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain
    struct SwapchainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    static SwapchainSupportDetails querySwapchainSupport(
        VkPhysicalDevice physicalDevice,
        VkSurfaceKHR surface
    );

private:
    // ========================================================================
    // [TODO 2] 选择表面格式（颜色空间）
    // ========================================================================
    // CONCEPT: 选择最佳的颜色格式和颜色空间
    //
    // 常见格式：
    // - VK_FORMAT_B8G8R8A8_SRGB：BGRA 8-bit sRGB（推荐）
    // - VK_FORMAT_R8G8B8A8_SRGB：RGBA 8-bit sRGB
    //
    // 颜色空间：
    // - VK_COLOR_SPACE_SRGB_NONLINEAR_KHR：标准sRGB（推荐）
    //
    // YOU NEED TO:
    // 1. 遍历 availableFormats
    // 2. 优先选择 B8G8R8A8_SRGB + SRGB_NONLINEAR
    // 3. 如果没有，返回第一个可用的
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats
    );

    // ========================================================================
    // [TODO 3] 选择呈现模式
    // ========================================================================
    // CONCEPT: 控制图像如何呈现到屏幕
    //
    // 常见模式：
    // - VK_PRESENT_MODE_IMMEDIATE_KHR：立即呈现（可能撕裂）
    // - VK_PRESENT_MODE_FIFO_KHR：队列模式（垂直同步，保证有）
    // - VK_PRESENT_MODE_MAILBOX_KHR：三缓冲（低延迟，高性能）
    //
    // YOU NEED TO:
    // 1. 优先选择 MAILBOX（如果可用）
    // 2. 否则使用 FIFO（保证可用）
    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes
    );

    // ========================================================================
    // [TODO 4] 选择交换范围（分辨率）
    // ========================================================================
    // CONCEPT: 确定交换链图像的分辨率
    //
    // YOU NEED TO:
    // 1. 检查 capabilities.currentExtent
    // 2. 如果是 UINT32_MAX，使用窗口实际大小
    // 3. 限制在 minImageExtent 和 maxImageExtent 之间
    //
    // TIPS: 使用 glfwGetFramebufferSize() 获取窗口大小（像素）
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    // ========================================================================
    // [TODO 5] 创建交换链
    // ========================================================================
    // CONCEPT: 实际创建 VkSwapchainKHR 对象
    //
    // YOU NEED TO:
    // 1. 查询支持的功能（调用 querySwapchainSupport）
    // 2. 选择格式、呈现模式、范围（调用上面的choose函数）
    // 3. 确定图像数量（推荐 minImageCount + 1）
    // 4. 填充 VkSwapchainCreateInfoKHR
    // 5. 调用 vkCreateSwapchainKHR()
    // 6. 获取交换链图像（vkGetSwapchainImagesKHR）
    //
    // IMPORTANT:
    // - 如果graphics和present队列不同，使用 VK_SHARING_MODE_CONCURRENT
    // - 如果相同，使用 VK_SHARING_MODE_EXCLUSIVE（性能更好）
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain
    void createSwapchain();

    // ========================================================================
    // [TODO 6] 创建图像视图
    // ========================================================================
    // CONCEPT: VkImageView 是访问 VkImage 的"窗口"
    //
    // 为什么需要ImageView？
    // - VkImage是原始图像数据
    // - VkImageView描述如何访问它（格式、mip层级、数组层等）
    // - 类比：Image是文件，ImageView是文件指针
    //
    // YOU NEED TO:
    // 1. 为每个交换链图像创建一个ImageView
    // 2. 填充 VkImageViewCreateInfo：
    //    - image: 交换链图像
    //    - viewType: VK_IMAGE_VIEW_TYPE_2D
    //    - format: m_imageFormat
    //    - components: VK_COMPONENT_SWIZZLE_IDENTITY（不重映射）
    //    - subresourceRange: 颜色图像，1 mip，1 layer
    // 3. 调用 vkCreateImageView()
    void createImageViews();

    // Vulkan对象
    VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> m_images;               // 交换链图像（由Vulkan管理）
    std::vector<VkImageView> m_imageViews;       // 图像视图（需要手动销毁）

    VkFormat m_imageFormat;
    VkExtent2D m_extent;

    // 外部引用（不拥有）
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device = VK_NULL_HANDLE;
    VkSurfaceKHR m_surface = VK_NULL_HANDLE;
    Window* m_window = nullptr;
};
