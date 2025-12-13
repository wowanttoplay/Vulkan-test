#pragma once

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>

/**
 * @brief Vulkan缓冲区管理（使用VMA）
 *
 * ========================================================================
 * [学习模块 4] VULKAN BUFFERS & MEMORY
 * ========================================================================
 *
 * BUFFER是什么？
 * - GPU上的线性内存块
 * - 存储顶点、索引、uniform数据等
 * - 必须显式管理生命周期
 *
 * 为什么使用VMA？
 * - Vulkan的内存管理非常复杂
 * - VMA (Vulkan Memory Allocator) 简化了内存分配
 * - 自动处理内存池、碎片整理等
 *
 * 常见BUFFER类型：
 * - Vertex Buffer：顶点数据（位置、法线、UV等）
 * - Index Buffer：索引数据（三角形顶点索引）
 * - Uniform Buffer：shader常量（变换矩阵、光照参数）
 * - Staging Buffer：CPU→GPU数据传输的临时缓冲
 *
 * 内存位置：
 * - GPU_ONLY：仅GPU可访问（最快，用于顶点/索引）
 * - CPU_TO_GPU：CPU写，GPU读（用于uniform）
 * - GPU_TO_CPU：GPU写，CPU读（用于readback）
 *
 * 数据传输流程：
 * 1. 创建Staging Buffer（CPU可访问）
 * 2. 写入数据到Staging Buffer
 * 3. 创建Device Buffer（GPU专用）
 * 4. 复制 Staging → Device
 * 5. 销毁Staging Buffer
 *
 * 你需要实现：
 * 1. create() - 创建缓冲区和分配内存
 * 2. map/unmap() - 映射内存用于CPU访问
 * 3. copyFrom() - 从另一个buffer复制数据
 */
class VulkanBuffer {
public:
    VulkanBuffer() = default;
    ~VulkanBuffer();

    // ========================================================================
    // [TODO 1] 创建缓冲区
    // ========================================================================
    // CONCEPT: 创建VkBuffer并分配内存
    //
    // VkBuffer vs 内存：
    // - VkBuffer：缓冲区对象（逻辑概念）
    // - VkDeviceMemory：实际的GPU内存
    // - 需要将两者绑定在一起
    //
    // VMA简化了这个过程！
    //
    // YOU NEED TO:
    // 1. 填充 VkBufferCreateInfo：
    //    - size: 缓冲区大小（字节）
    //    - usage: 用途标志（VK_BUFFER_USAGE_VERTEX_BUFFER_BIT等）
    //    - sharingMode: VK_SHARING_MODE_EXCLUSIVE（一般情况）
    // 2. 填充 VmaAllocationCreateInfo：
    //    - usage: VMA_MEMORY_USAGE_AUTO
    //    - flags: 根据memoryLocation设置（见下面）
    // 3. 调用 vmaCreateBuffer()
    //
    // memoryLocation映射：
    // - GPU_ONLY → flags = 0（默认）
    // - CPU_TO_GPU → flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT
    // - GPU_TO_CPU → flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Vertex_buffers/Vertex_buffer_creation
    // VMA DOCS: https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/
    enum class MemoryLocation {
        GPU_ONLY,      // 最快，仅GPU访问（顶点、索引缓冲）
        CPU_TO_GPU,    // CPU写，GPU读（uniform缓冲）
        GPU_TO_CPU     // GPU写，CPU读（readback）
    };

    void create(
        VmaAllocator allocator,
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        MemoryLocation memoryLocation
    );

    void cleanup();

    // ========================================================================
    // [TODO 2] 映射内存（CPU访问）
    // ========================================================================
    // CONCEPT: 获取缓冲区的CPU可访问指针
    //
    // 为什么需要map？
    // - GPU内存默认CPU不能直接访问
    // - map()获取指针，可以像普通内存一样读写
    // - unmap()后GPU才能安全使用
    //
    // YOU NEED TO:
    // 1. map(): 调用 vmaMapMemory()，返回 void* 指针
    // 2. unmap(): 调用 vmaUnmapMemory()
    //
    // USAGE:
    //   void* data = buffer.map();
    //   memcpy(data, vertices, sizeof(vertices));
    //   buffer.unmap();
    //
    // IMPORTANT: 只有CPU_TO_GPU或GPU_TO_CPU的缓冲可以map
    void* map();
    void unmap();

    // ========================================================================
    // [TODO 3] 从另一个缓冲复制数据
    // ========================================================================
    // CONCEPT: GPU→GPU 数据复制
    //
    // 为什么需要？
    // - Staging Buffer（CPU可写） → Device Buffer（GPU专用）
    // - GPU专用内存性能最好，但CPU不能直接写入
    //
    // YOU NEED TO:
    // 1. 分配临时 VkCommandBuffer（使用传入的commandPool）
    // 2. 开始记录命令（vkBeginCommandBuffer）
    // 3. 记录复制命令（vkCmdCopyBuffer）：
    //    - VkBufferCopy：srcOffset, dstOffset, size
    // 4. 结束记录（vkEndCommandBuffer）
    // 5. 提交到队列（vkQueueSubmit）
    // 6. 等待完成（vkQueueWaitIdle）
    // 7. 释放临时CommandBuffer
    //
    // TIPS:
    // - 这是一个同步操作（会等待GPU完成）
    // - 生产环境应该使用异步传输队列
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Vertex_buffers/Staging_buffer
    void copyFrom(
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        VulkanBuffer& srcBuffer,
        VkDeviceSize size
    );

    // Getters
    VkBuffer getHandle() const { return m_buffer; }
    VkDeviceSize getSize() const { return m_size; }

private:
    VkBuffer m_buffer = VK_NULL_HANDLE;
    VmaAllocation m_allocation = VK_NULL_HANDLE;
    VmaAllocator m_allocator = VK_NULL_HANDLE;
    VkDeviceSize m_size = 0;

    bool m_mapped = false;
};

/**
 * @brief 辅助函数：创建并上传数据到GPU
 *
 * USAGE EXAMPLE:
 *   std::vector<Vertex> vertices = {...};
 *   VulkanBuffer vertexBuffer = createBufferWithData(
 *       allocator,
 *       device,
 *       queue,
 *       commandPool,
 *       vertices.data(),
 *       sizeof(Vertex) * vertices.size(),
 *       VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
 *   );
 */
VulkanBuffer createBufferWithData(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    const void* data,
    VkDeviceSize size,
    VkBufferUsageFlags usage
);
