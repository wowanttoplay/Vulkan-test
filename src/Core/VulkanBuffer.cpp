#include "Core/VulkanBuffer.h"
#include <stdexcept>

VulkanBuffer::~VulkanBuffer() {
    cleanup();
}

void VulkanBuffer::cleanup() {
    if (m_buffer != VK_NULL_HANDLE && m_allocator != VK_NULL_HANDLE) {
        vmaDestroyBuffer(m_allocator, m_buffer, m_allocation);
        m_buffer = VK_NULL_HANDLE;
        m_allocation = VK_NULL_HANDLE;
    }
}

// ============================================================================
// [TODO 1] CREATE BUFFER
// ============================================================================
void VulkanBuffer::create(
    VmaAllocator allocator,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    MemoryLocation memoryLocation
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  create() in VulkanBuffer.cpp\n"
        "\n"
        "TASK:\n"
        "  Create buffer using VMA\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanBuffer.cpp:19\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanBuffer.h (TODO 1 comments)\n"
        "  - https://vulkan-tutorial.com/Vertex_buffers/Vertex_buffer_creation\n"
        "  - VMA docs: https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 4.1\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 2] MAP MEMORY
// ============================================================================
void* VulkanBuffer::map() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  map() in VulkanBuffer.cpp\n"
        "\n"
        "TASK:\n"
        "  Map buffer memory for CPU access\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanBuffer.cpp:42\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanBuffer.h (TODO 2 comments)\n"
        "  - https://vulkan-tutorial.com/Vertex_buffers/Staging_buffer\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 4.2\n"
        "========================================\n"
    );
}

void VulkanBuffer::unmap() {
    if (!m_mapped) return;
    vmaUnmapMemory(m_allocator, m_allocation);
    m_mapped = false;
}

// ============================================================================
// [TODO 3] COPY FROM BUFFER
// ============================================================================
void VulkanBuffer::copyFrom(
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    VulkanBuffer& srcBuffer,
    VkDeviceSize size
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  copyFrom() in VulkanBuffer.cpp\n"
        "\n"
        "TASK:\n"
        "  Copy data from source buffer to this buffer\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanBuffer.cpp:70\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanBuffer.h (TODO 3 comments)\n"
        "  - https://vulkan-tutorial.com/Vertex_buffers/Staging_buffer\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 4.3\n"
        "========================================\n"
    );
}

// ============================================================================
// Helper Function
// ============================================================================
VulkanBuffer createBufferWithData(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    const void* data,
    VkDeviceSize size,
    VkBufferUsageFlags usage
) {
    // Create staging buffer (CPU accessible)
    VulkanBuffer stagingBuffer;
    stagingBuffer.create(
        allocator,
        size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VulkanBuffer::MemoryLocation::CPU_TO_GPU
    );

    // Copy data to staging buffer
    void* mappedData = stagingBuffer.map();
    memcpy(mappedData, data, size);
    stagingBuffer.unmap();

    // Create device buffer (GPU only)
    VulkanBuffer deviceBuffer;
    deviceBuffer.create(
        allocator,
        size,
        usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VulkanBuffer::MemoryLocation::GPU_ONLY
    );

    // Copy staging -> device
    deviceBuffer.copyFrom(device, queue, commandPool, stagingBuffer, size);

    // Cleanup staging buffer
    stagingBuffer.cleanup();

    return deviceBuffer;
}
