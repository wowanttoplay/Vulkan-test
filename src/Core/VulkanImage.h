#pragma once

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <string>

/**
 * @brief Vulkan图像（纹理）管理
 *
 * ========================================================================
 * [学习模块 5] VULKAN IMAGES & TEXTURES
 * ========================================================================
 *
 * IMAGE是什么？
 * - GPU上的2D/3D像素数据
 * - 可以是纹理、渲染目标、深度缓冲等
 * - 比Buffer更复杂（有格式、mipmap、多采样等）
 *
 * IMAGE vs BUFFER：
 * - Buffer：线性内存（1D数组）
 * - Image：多维、有格式、可采样的数据
 *
 * IMAGE VIEW：
 * - 访问Image的"窗口"
 * - 类似于Buffer的指针
 * - 可以有不同的格式、mip层级
 *
 * SAMPLER：
 * - 控制如何采样纹理
 * - 过滤模式（线性、最近邻）
 * - 寻址模式（重复、钳位、镜像）
 * - Mipmap设置
 *
 * IMAGE LAYOUT：
 * - Vulkan的Image有不同的"布局"
 * - 不同操作需要不同的布局
 * - 必须显式转换布局（layout transition）
 *
 * 常见布局：
 * - UNDEFINED：初始状态（内容未定义）
 * - TRANSFER_DST_OPTIMAL：作为复制目标（上传纹理）
 * - SHADER_READ_ONLY_OPTIMAL：shader采样（最常用）
 * - COLOR_ATTACHMENT_OPTIMAL：作为颜色附件（渲染目标）
 * - DEPTH_STENCIL_ATTACHMENT_OPTIMAL：深度/模板附件
 *
 * 你需要实现：
 * 1. create() - 创建图像
 * 2. createView() - 创建图像视图
 * 3. createSampler() - 创建采样器
 * 4. transitionLayout() - 转换布局
 * 5. copyFromBuffer() - 从buffer上传数据
 * 6. loadFromFile() - 从文件加载纹理（综合应用）
 */
class VulkanImage {
public:
    VulkanImage() = default;
    ~VulkanImage();

    // ========================================================================
    // [TODO 1] 创建图像
    // ========================================================================
    // CONCEPT: 创建VkImage并分配内存
    //
    // YOU NEED TO:
    // 1. 填充 VkImageCreateInfo：
    //    - imageType: VK_IMAGE_TYPE_2D（2D纹理）
    //    - format: 图像格式（VK_FORMAT_R8G8B8A8_SRGB等）
    //    - extent: 宽、高、深度
    //    - mipLevels: mipmap层级数（Phase 1可以是1）
    //    - arrayLayers: 数组层数（立方体贴图是6）
    //    - samples: VK_SAMPLE_COUNT_1_BIT（无多采样）
    //    - tiling: VK_IMAGE_TILING_OPTIMAL（GPU优化布局）
    //    - usage: VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT
    //    - initialLayout: VK_IMAGE_LAYOUT_UNDEFINED
    // 2. 填充 VmaAllocationCreateInfo：
    //    - usage: VMA_MEMORY_USAGE_AUTO
    //    - flags: 0（GPU only）
    // 3. 调用 vmaCreateImage()
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Texture_mapping/Images
    void create(
        VmaAllocator allocator,
        uint32_t width,
        uint32_t height,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        uint32_t mipLevels = 1
    );

    // ========================================================================
    // [TODO 2] 创建图像视图
    // ========================================================================
    // CONCEPT: ImageView是访问Image的接口
    //
    // YOU NEED TO:
    // 1. 填充 VkImageViewCreateInfo：
    //    - image: m_image
    //    - viewType: VK_IMAGE_VIEW_TYPE_2D
    //    - format: m_format
    //    - components: 全部设为 VK_COMPONENT_SWIZZLE_IDENTITY
    //    - subresourceRange:
    //      - aspectMask: VK_IMAGE_ASPECT_COLOR_BIT（颜色图像）
    //                    VK_IMAGE_ASPECT_DEPTH_BIT（深度图像）
    //      - baseMipLevel: 0
    //      - levelCount: m_mipLevels
    //      - baseArrayLayer: 0
    //      - layerCount: 1
    // 2. 调用 vkCreateImageView()
    void createView(VkDevice device, VkImageAspectFlags aspectFlags);

    // ========================================================================
    // [TODO 3] 创建采样器
    // ========================================================================
    // CONCEPT: Sampler控制如何在shader中采样纹理
    //
    // YOU NEED TO:
    // 1. 填充 VkSamplerCreateInfo：
    //    - magFilter: VK_FILTER_LINEAR（放大时线性插值）
    //    - minFilter: VK_FILTER_LINEAR（缩小时线性插值）
    //    - mipmapMode: VK_SAMPLER_MIPMAP_MODE_LINEAR
    //    - addressModeU/V/W: VK_SAMPLER_ADDRESS_MODE_REPEAT（重复）
    //    - mipLodBias: 0.0f
    //    - anisotropyEnable: VK_TRUE
    //    - maxAnisotropy: 16.0f（各向异性过滤）
    //    - compareEnable: VK_FALSE
    //    - minLod: 0.0f
    //    - maxLod: static_cast<float>(m_mipLevels)
    //    - borderColor: VK_BORDER_COLOR_INT_OPAQUE_BLACK
    //    - unnormalizedCoordinates: VK_FALSE
    // 2. 调用 vkCreateSampler()
    //
    // IMPORTANT: 检查GPU是否支持各向异性过滤
    //   VkPhysicalDeviceFeatures features;
    //   vkGetPhysicalDeviceFeatures(physicalDevice, &features);
    //   if (!features.samplerAnisotropy) { disable it }
    void createSampler(VkDevice device, VkPhysicalDevice physicalDevice);

    // ========================================================================
    // [TODO 4] 转换图像布局
    // ========================================================================
    // CONCEPT: 图像需要在不同布局之间转换
    //
    // 为什么需要？
    // - 不同操作需要不同的布局（性能优化）
    // - 例如：上传时需要TRANSFER_DST，采样时需要SHADER_READ_ONLY
    //
    // YOU NEED TO:
    // 1. 分配临时CommandBuffer
    // 2. 填充 VkImageMemoryBarrier：
    //    - oldLayout: 旧布局
    //    - newLayout: 新布局
    //    - srcQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED
    //    - dstQueueFamilyIndex: VK_QUEUE_FAMILY_IGNORED
    //    - image: m_image
    //    - subresourceRange: aspectMask, baseMipLevel, levelCount, etc.
    //    - srcAccessMask: 根据oldLayout设置（见下面）
    //    - dstAccessMask: 根据newLayout设置
    // 3. 记录 vkCmdPipelineBarrier()
    // 4. 提交并等待
    //
    // AccessMask映射（常见情况）：
    // - UNDEFINED → TRANSFER_DST:
    //   srcAccess = 0, dstAccess = TRANSFER_WRITE
    //   srcStage = TOP_OF_PIPE, dstStage = TRANSFER
    // - TRANSFER_DST → SHADER_READ_ONLY:
    //   srcAccess = TRANSFER_WRITE, dstAccess = SHADER_READ
    //   srcStage = TRANSFER, dstStage = FRAGMENT_SHADER
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Texture_mapping/Images#page_Layout-transitions
    void transitionLayout(
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        VkImageLayout oldLayout,
        VkImageLayout newLayout
    );

    // ========================================================================
    // [TODO 5] 从Buffer复制数据到Image
    // ========================================================================
    // CONCEPT: 将CPU数据（通过Staging Buffer）上传到GPU纹理
    //
    // YOU NEED TO:
    // 1. 分配临时CommandBuffer
    // 2. 填充 VkBufferImageCopy：
    //    - bufferOffset: 0
    //    - bufferRowLength: 0（紧密打包）
    //    - bufferImageHeight: 0
    //    - imageSubresource: aspectMask, mipLevel, baseArrayLayer, layerCount
    //    - imageOffset: {0, 0, 0}
    //    - imageExtent: {width, height, 1}
    // 3. 记录 vkCmdCopyBufferToImage()
    // 4. 提交并等待
    //
    // IMPORTANT: Image必须在TRANSFER_DST_OPTIMAL布局
    void copyFromBuffer(
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        VkBuffer buffer,
        uint32_t width,
        uint32_t height
    );

    // ========================================================================
    // [TODO 6] 从文件加载纹理（综合应用）
    // ========================================================================
    // CONCEPT: 组合上面所有功能，完成纹理加载
    //
    // WORKFLOW:
    // 1. 使用stb_image加载图像文件
    //    - stbi_load() 返回像素数据（RGBA）
    // 2. 创建Staging Buffer（CPU_TO_GPU）
    // 3. 上传像素数据到Staging Buffer
    // 4. 创建Image（GPU only）
    // 5. 转换布局：UNDEFINED → TRANSFER_DST_OPTIMAL
    // 6. 复制 Staging Buffer → Image
    // 7. 转换布局：TRANSFER_DST → SHADER_READ_ONLY_OPTIMAL
    // 8. 销毁Staging Buffer
    // 9. 创建ImageView和Sampler
    //
    // YOU NEED TO:
    // - 实现上述流程
    // - 处理错误（文件不存在、格式不支持等）
    // - 记得释放stb_image分配的内存（stbi_image_free）
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Texture_mapping/Images
    void loadFromFile(
        VmaAllocator allocator,
        VkDevice device,
        VkPhysicalDevice physicalDevice,
        VkQueue queue,
        VkCommandPool commandPool,
        const std::string& filepath
    );

    void cleanup();

    // Getters
    VkImage getHandle() const { return m_image; }
    VkImageView getView() const { return m_imageView; }
    VkSampler getSampler() const { return m_sampler; }
    VkFormat getFormat() const { return m_format; }
    uint32_t getWidth() const { return m_width; }
    uint32_t getHeight() const { return m_height; }

private:
    VkImage m_image = VK_NULL_HANDLE;
    VmaAllocation m_allocation = VK_NULL_HANDLE;
    VkImageView m_imageView = VK_NULL_HANDLE;
    VkSampler m_sampler = VK_NULL_HANDLE;

    VkFormat m_format = VK_FORMAT_UNDEFINED;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    uint32_t m_mipLevels = 1;

    // 外部引用
    VmaAllocator m_allocator = VK_NULL_HANDLE;
    VkDevice m_device = VK_NULL_HANDLE;
};
