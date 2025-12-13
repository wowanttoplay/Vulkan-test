#include "Rendering/Mesh.h"
#include <cstring>
#include <cmath>

// ============================================================================
// Vertex描述
// ============================================================================

VkVertexInputBindingDescription Vertex::getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return bindingDescription;
}

std::vector<VkVertexInputAttributeDescription> Vertex::getAttributeDescriptions() {
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(4);

    // Location 0: position
    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, position);

    // Location 1: color
    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    // Location 2: normal
    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[2].offset = offsetof(Vertex, normal);

    // Location 3: texCoord
    attributeDescriptions[3].binding = 0;
    attributeDescriptions[3].location = 3;
    attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[3].offset = offsetof(Vertex, texCoord);

    return attributeDescriptions;
}

// ============================================================================
// Mesh实现
// ============================================================================

Mesh::~Mesh() {
    cleanup();
}

void Mesh::create(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    const std::vector<Vertex>& vertices,
    const std::vector<uint32_t>& indices
) {
    m_device = device;
    m_vertices = vertices;
    m_indices = indices;

    // 创建顶点缓冲
    VkDeviceSize vertexBufferSize = sizeof(Vertex) * vertices.size();
    m_vertexBuffer = createBufferWithData(
        allocator,
        device,
        queue,
        commandPool,
        vertices.data(),
        vertexBufferSize,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
    );

    // 创建索引缓冲
    VkDeviceSize indexBufferSize = sizeof(uint32_t) * indices.size();
    m_indexBuffer = createBufferWithData(
        allocator,
        device,
        queue,
        commandPool,
        indices.data(),
        indexBufferSize,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT
    );
}

void Mesh::cleanup() {
    m_vertexBuffer.cleanup();
    m_indexBuffer.cleanup();
}

void Mesh::draw(VkCommandBuffer commandBuffer) const {
    // 绑定顶点缓冲
    VkBuffer vertexBuffers[] = { m_vertexBuffer.getHandle() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    // 绑定索引缓冲
    vkCmdBindIndexBuffer(commandBuffer, m_indexBuffer.getHandle(), 0, VK_INDEX_TYPE_UINT32);

    // 绘制
    vkCmdDrawIndexed(commandBuffer, getIndexCount(), 1, 0, 0, 0);
}

// ============================================================================
// 基础几何体创建
// ============================================================================

Mesh Mesh::createCube(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool
) {
    // 立方体顶点（每个面不同颜色）
    std::vector<Vertex> vertices = {
        // Front face (红色)
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // Back face (绿色)
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

        // Top face (蓝色)
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        // Bottom face (黄色)
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},

        // Right face (品红)
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Left face (青色)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    };

    // 索引（每个面2个三角形）
    std::vector<uint32_t> indices = {
        0,  1,  2,  2,  3,  0,   // Front
        4,  5,  6,  6,  7,  4,   // Back
        8,  9,  10, 10, 11, 8,   // Top
        12, 13, 14, 14, 15, 12,  // Bottom
        16, 17, 18, 18, 19, 16,  // Right
        20, 21, 22, 22, 23, 20   // Left
    };

    Mesh mesh;
    mesh.create(allocator, device, queue, commandPool, vertices, indices);
    return mesh;
}

Mesh Mesh::createPlane(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    float size
) {
    float halfSize = size * 0.5f;

    std::vector<Vertex> vertices = {
        {{-halfSize, 0.0f, -halfSize}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ halfSize, 0.0f, -halfSize}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ halfSize, 0.0f,  halfSize}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-halfSize, 0.0f,  halfSize}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        2, 3, 0
    };

    Mesh mesh;
    mesh.create(allocator, device, queue, commandPool, vertices, indices);
    return mesh;
}

Mesh Mesh::createSphere(
    VmaAllocator allocator,
    VkDevice device,
    VkQueue queue,
    VkCommandPool commandPool,
    float radius,
    uint32_t segments
) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    const float PI = 3.14159265359f;

    // 生成顶点
    for (uint32_t lat = 0; lat <= segments; ++lat) {
        float theta = lat * PI / segments;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        for (uint32_t lon = 0; lon <= segments; ++lon) {
            float phi = lon * 2.0f * PI / segments;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            glm::vec3 position(
                radius * sinTheta * cosPhi,
                radius * cosTheta,
                radius * sinTheta * sinPhi
            );

            glm::vec3 normal = glm::normalize(position);
            glm::vec3 color(0.8f, 0.8f, 0.8f);
            glm::vec2 texCoord(
                static_cast<float>(lon) / segments,
                static_cast<float>(lat) / segments
            );

            vertices.push_back({position, color, normal, texCoord});
        }
    }

    // 生成索引
    for (uint32_t lat = 0; lat < segments; ++lat) {
        for (uint32_t lon = 0; lon < segments; ++lon) {
            uint32_t first = lat * (segments + 1) + lon;
            uint32_t second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    Mesh mesh;
    mesh.create(allocator, device, queue, commandPool, vertices, indices);
    return mesh;
}
