#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

/**
 * @brief Vulkan图形管线构建器
 *
 * ========================================================================
 * [学习模块 3] VULKAN GRAPHICS PIPELINE
 * ========================================================================
 *
 * PIPELINE是什么？
 * - 图形管线是GPU上的渲染流程
 * - 定义了顶点如何变成像素的整个过程
 * - Vulkan需要你显式配置每个阶段
 *
 * 管线的主要阶段：
 * 1. Input Assembly：如何组装顶点（点、线、三角形）
 * 2. Vertex Shader：顶点着色器（变换顶点）
 * 3. Rasterization：光栅化（将三角形转换为片段）
 * 4. Fragment Shader：片段着色器（计算像素颜色）
 * 5. Color Blending：颜色混合（透明度等）
 * 6. Depth/Stencil Testing：深度/模板测试
 *
 * 为什么这么复杂？
 * - 灵活性：你可以精确控制每个细节
 * - 性能：驱动程序可以优化整个管线
 * - 不可变性：管线创建后不能修改（但可以切换）
 *
 * PIPELINE LAYOUT：
 * - 定义shader可以访问的资源（uniform buffers, textures）
 * - 类似于shader的"函数签名"
 *
 * RENDER PASS：
 * - 定义渲染目标（颜色、深度缓冲）
 * - 定义如何加载/存储附件
 * - 多个subpass可以共享数据
 *
 * 你需要实现：
 * 1. loadShader() - 加载SPIR-V着色器
 * 2. createPipelineLayout() - 创建管线布局
 * 3. build() - 构建完整的图形管线
 */
class VulkanPipelineBuilder {
public:
    VulkanPipelineBuilder(VkDevice device);
    ~VulkanPipelineBuilder();

    // 配置管线的各个阶段
    VulkanPipelineBuilder& setShaders(
        const std::string& vertPath,
        const std::string& fragPath
    );

    VulkanPipelineBuilder& setVertexInput(
        const std::vector<VkVertexInputBindingDescription>& bindings,
        const std::vector<VkVertexInputAttributeDescription>& attributes
    );

    VulkanPipelineBuilder& setInputAssembly(
        VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        VkBool32 primitiveRestart = VK_FALSE
    );

    VulkanPipelineBuilder& setViewport(VkExtent2D extent);

    VulkanPipelineBuilder& setRasterizer(
        VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL,
        VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT,
        VkFrontFace frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE
    );

    VulkanPipelineBuilder& setMultisampling(
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT
    );

    VulkanPipelineBuilder& setDepthStencil(
        VkBool32 depthTest = VK_TRUE,
        VkBool32 depthWrite = VK_TRUE,
        VkCompareOp depthCompare = VK_COMPARE_OP_LESS
    );

    VulkanPipelineBuilder& setColorBlending(
        VkBool32 blendEnable = VK_FALSE
    );

    VulkanPipelineBuilder& setDescriptorSetLayout(
        VkDescriptorSetLayout layout
    );

    VulkanPipelineBuilder& setRenderPass(
        VkRenderPass renderPass,
        uint32_t subpass = 0
    );

    // ========================================================================
    // [TODO 1] 加载SPIR-V着色器
    // ========================================================================
    // CONCEPT: Vulkan只接受SPIR-V格式的着色器（二进制）
    //
    // SPIR-V是什么？
    // - Standard Portable Intermediate Representation
    // - 着色器的中间表示（类似于字节码）
    // - GLSL/HLSL编译成SPIR-V，Vulkan使用SPIR-V
    //
    // YOU NEED TO:
    // 1. 读取SPIR-V文件到内存（std::ifstream, binary mode）
    // 2. 填充 VkShaderModuleCreateInfo：
    //    - codeSize: 文件大小
    //    - pCode: 指向SPIR-V字节码的指针（需要reinterpret_cast<uint32_t*>）
    // 3. 调用 vkCreateShaderModule()
    // 4. 返回 VkShaderModule
    //
    // TIPS:
    // - 使用 std::ifstream::ate 可以直接获取文件大小
    // - SPIR-V是uint32_t数组，需要正确对齐
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules
    VkShaderModule loadShader(const std::string& filepath);

    // ========================================================================
    // [TODO 2] 创建管线布局
    // ========================================================================
    // CONCEPT: Pipeline Layout定义shader可以访问的资源
    //
    // 包含：
    // - Descriptor Set Layouts：uniform buffers, textures等
    // - Push Constants：小量快速数据（变换矩阵等）
    //
    // YOU NEED TO:
    // 1. 填充 VkPipelineLayoutCreateInfo：
    //    - setLayoutCount: descriptor set布局数量
    //    - pSetLayouts: descriptor set布局数组
    //    - pushConstantRangeCount: push constant数量（Phase 1可以是0）
    // 2. 调用 vkCreatePipelineLayout()
    //
    // PHASE 1: 可以先创建空的layout（没有descriptors和push constants）
    // LATER: 添加uniform buffer和texture descriptors
    void createPipelineLayout();

    // ========================================================================
    // [TODO 3] 构建图形管线
    // ========================================================================
    // CONCEPT: 将所有配置组合成最终的VkPipeline
    //
    // 主要步骤：
    // 1. Shader Stages：配置顶点和片段着色器
    // 2. Vertex Input：顶点数据格式
    // 3. Input Assembly：如何组装顶点
    // 4. Viewport & Scissor：渲染区域
    // 5. Rasterization：光栅化设置
    // 6. Multisampling：多重采样（抗锯齿）
    // 7. Depth/Stencil：深度测试
    // 8. Color Blending：颜色混合
    // 9. Dynamic State：可以动态修改的状态（viewport, scissor等）
    //
    // YOU NEED TO:
    // 1. 加载着色器（调用loadShader）
    // 2. 创建 VkPipelineShaderStageCreateInfo[] 数组（vertex + fragment）
    // 3. 填充所有固定功能阶段的CreateInfo结构体：
    //    - VkPipelineVertexInputStateCreateInfo
    //    - VkPipelineInputAssemblyStateCreateInfo
    //    - VkPipelineViewportStateCreateInfo
    //    - VkPipelineRasterizationStateCreateInfo
    //    - VkPipelineMultisampleStateCreateInfo
    //    - VkPipelineDepthStencilStateCreateInfo
    //    - VkPipelineColorBlendStateCreateInfo
    //    - VkPipelineDynamicStateCreateInfo（可选）
    // 4. 填充 VkGraphicsPipelineCreateInfo
    // 5. 调用 vkCreateGraphicsPipelines()
    // 6. 销毁shader modules（pipeline创建后不再需要）
    //
    // TIPS:
    // - 使用builder模式收集的配置（m_xxx成员变量）
    // - Dynamic state可以让viewport和scissor在运行时修改
    //
    // VULKAN TUTORIAL: https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Conclusion
    VkPipeline build();

    // Getters
    VkPipelineLayout getLayout() const { return m_pipelineLayout; }

    void cleanup();

private:
    VkDevice m_device;

    // 管线配置（由builder方法设置）
    std::string m_vertShaderPath;
    std::string m_fragShaderPath;
    std::vector<VkVertexInputBindingDescription> m_vertexBindings;
    std::vector<VkVertexInputAttributeDescription> m_vertexAttributes;
    VkPrimitiveTopology m_topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    VkBool32 m_primitiveRestart = VK_FALSE;
    VkExtent2D m_extent = {0, 0};
    VkPolygonMode m_polygonMode = VK_POLYGON_MODE_FILL;
    VkCullModeFlags m_cullMode = VK_CULL_MODE_BACK_BIT;
    VkFrontFace m_frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    VkSampleCountFlagBits m_samples = VK_SAMPLE_COUNT_1_BIT;
    VkBool32 m_depthTest = VK_TRUE;
    VkBool32 m_depthWrite = VK_TRUE;
    VkCompareOp m_depthCompare = VK_COMPARE_OP_LESS;
    VkBool32 m_blendEnable = VK_FALSE;
    VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
    VkRenderPass m_renderPass = VK_NULL_HANDLE;
    uint32_t m_subpass = 0;

    // Vulkan对象
    VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
};
