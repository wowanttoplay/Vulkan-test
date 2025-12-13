#include "Core/VulkanImage.h"
#include <stdexcept>

VulkanImage::~VulkanImage() {
    cleanup();
}

void VulkanImage::cleanup() {
    if (m_sampler != VK_NULL_HANDLE) {
        vkDestroySampler(m_device, m_sampler, nullptr);
        m_sampler = VK_NULL_HANDLE;
    }

    if (m_imageView != VK_NULL_HANDLE) {
        vkDestroyImageView(m_device, m_imageView, nullptr);
        m_imageView = VK_NULL_HANDLE;
    }

    if (m_image != VK_NULL_HANDLE && m_allocator != VK_NULL_HANDLE) {
        vmaDestroyImage(m_allocator, m_image, m_allocation);
        m_image = VK_NULL_HANDLE;
        m_allocation = VK_NULL_HANDLE;
    }
}

// ============================================================================
// [TODO 1] CREATE IMAGE
// ============================================================================
void VulkanImage::create(
    VmaAllocator allocator,
    uint32_t width,
    uint32_t height,
    VkFormat format,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    uint32_t mipLevels
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  create() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Create image using VMA\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:32\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 1 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Images\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 2] CREATE IMAGE VIEW
// ============================================================================
void VulkanImage::createView(VkDevice device, VkImageAspectFlags aspectFlags) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createView() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Create image view\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:55\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 2 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Image_view_and_sampler\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 3] CREATE SAMPLER
// ============================================================================
void VulkanImage::createSampler(VkDevice device, VkPhysicalDevice physicalDevice) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createSampler() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Create texture sampler\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:78\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 3 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Image_view_and_sampler\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 4] TRANSITION LAYOUT
// ============================================================================
void VulkanImage::transitionLayout(
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    VkImageLayout oldLayout,
    VkImageLayout newLayout
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  transitionLayout() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Transition image layout using pipeline barrier\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:101\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 4 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Images#page_Layout-transitions\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 5] COPY FROM BUFFER
// ============================================================================
void VulkanImage::copyFromBuffer(
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    VkBuffer buffer,
    uint32_t width,
    uint32_t height
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  copyFromBuffer() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Copy buffer data to image\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:127\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 5 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Images\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 6] LOAD FROM FILE
// ============================================================================
void VulkanImage::loadFromFile(
    VmaAllocator allocator,
    VkDevice device,
    VkPhysicalDevice physicalDevice,
    VkQueue queue,
    VkCommandPool commandPool,
    const std::string& filepath
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  loadFromFile() in VulkanImage.cpp\n"
        "\n"
        "TASK:\n"
        "  Load texture from file (using stb_image)\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanImage.cpp:153\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanImage.h (TODO 6 comments)\n"
        "  - https://vulkan-tutorial.com/Texture_mapping/Images\n"
        "\n"
        "NOTE:\n"
        "  This is optional for Phase 1 (needed for textures in Phase 2)\n"
        "========================================\n"
    );
}
