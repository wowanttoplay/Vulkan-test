#pragma once

#include "Core/VulkanBuffer.h"
#include <glm/glm.hpp>
#include <vector>

/**
 * @brief 顶点数据结构
 *
 * Phase 1：简单的顶点格式（位置 + 颜色）
 * Later：添加法线、UV、切线等
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;     // Phase 2: 用于光照
    glm::vec2 texCoord;   // Phase 2: 用于纹理

    // Vulkan顶点输入描述
    static VkVertexInputBindingDescription getBindingDescription();
    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};

/**
 * @brief 网格类 - 完整实现
 *
 * 职责：
 * - 存储顶点和索引数据
 * - 管理GPU缓冲区
 * - 提供渲染接口
 */
class Mesh {
public:
    Mesh() = default;
    ~Mesh();

    // 创建网格（上传到GPU）
    void create(
        VmaAllocator allocator,
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices
    );

    void cleanup();

    // 渲染（绑定并绘制）
    void draw(VkCommandBuffer commandBuffer) const;

    // Getters
    const std::vector<Vertex>& getVertices() const { return m_vertices; }
    const std::vector<uint32_t>& getIndices() const { return m_indices; }
    uint32_t getVertexCount() const { return static_cast<uint32_t>(m_vertices.size()); }
    uint32_t getIndexCount() const { return static_cast<uint32_t>(m_indices.size()); }

    // 辅助函数：创建基础几何体
    static Mesh createCube(
        VmaAllocator allocator,
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool
    );

    static Mesh createPlane(
        VmaAllocator allocator,
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        float size = 1.0f
    );

    static Mesh createSphere(
        VmaAllocator allocator,
        VkDevice device,
        VkQueue queue,
        VkCommandPool commandPool,
        float radius = 0.5f,
        uint32_t segments = 32
    );

private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;

    VulkanBuffer m_vertexBuffer;
    VulkanBuffer m_indexBuffer;

    VkDevice m_device = VK_NULL_HANDLE;
};
