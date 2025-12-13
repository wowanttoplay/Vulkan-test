#include "Core/VulkanPipeline.h"
#include "Rendering/Mesh.h"
#include <stdexcept>

VulkanPipelineBuilder::VulkanPipelineBuilder(VkDevice device)
    : m_device(device) {
}

VulkanPipelineBuilder::~VulkanPipelineBuilder() {
    cleanup();
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setShaders(
    const std::string& vertPath,
    const std::string& fragPath
) {
    m_vertShaderPath = vertPath;
    m_fragShaderPath = fragPath;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setVertexInput(
    const std::vector<VkVertexInputBindingDescription>& bindings,
    const std::vector<VkVertexInputAttributeDescription>& attributes
) {
    m_vertexBindings = bindings;
    m_vertexAttributes = attributes;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setInputAssembly(
    VkPrimitiveTopology topology,
    VkBool32 primitiveRestart
) {
    m_topology = topology;
    m_primitiveRestart = primitiveRestart;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setViewport(VkExtent2D extent) {
    m_extent = extent;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setRasterizer(
    VkPolygonMode polygonMode,
    VkCullModeFlags cullMode,
    VkFrontFace frontFace
) {
    m_polygonMode = polygonMode;
    m_cullMode = cullMode;
    m_frontFace = frontFace;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setMultisampling(VkSampleCountFlagBits samples) {
    m_samples = samples;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setDepthStencil(
    VkBool32 depthTest,
    VkBool32 depthWrite,
    VkCompareOp depthCompare
) {
    m_depthTest = depthTest;
    m_depthWrite = depthWrite;
    m_depthCompare = depthCompare;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setColorBlending(VkBool32 blendEnable) {
    m_blendEnable = blendEnable;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setDescriptorSetLayout(VkDescriptorSetLayout layout) {
    m_descriptorSetLayout = layout;
    return *this;
}

VulkanPipelineBuilder& VulkanPipelineBuilder::setRenderPass(VkRenderPass renderPass, uint32_t subpass) {
    m_renderPass = renderPass;
    m_subpass = subpass;
    return *this;
}

void VulkanPipelineBuilder::cleanup() {
    if (m_pipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
        m_pipelineLayout = VK_NULL_HANDLE;
    }
}

// ============================================================================
// [TODO 1] LOAD SHADER
// ============================================================================
VkShaderModule VulkanPipelineBuilder::loadShader(const std::string& filepath) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  loadShader() in VulkanPipeline.cpp\n"
        "\n"
        "TASK:\n"
        "  Load SPIR-V shader from file\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanPipeline.cpp:113\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanPipeline.h (TODO 1 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 3.1\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 2] CREATE PIPELINE LAYOUT
// ============================================================================
void VulkanPipelineBuilder::createPipelineLayout() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createPipelineLayout() in VulkanPipeline.cpp\n"
        "\n"
        "TASK:\n"
        "  Create pipeline layout (descriptor sets, push constants)\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanPipeline.cpp:134\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanPipeline.h (TODO 2 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Fixed_functions\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 3.2\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 3] BUILD PIPELINE
// ============================================================================
VkPipeline VulkanPipelineBuilder::build() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  build() in VulkanPipeline.cpp\n"
        "\n"
        "TASK:\n"
        "  Build graphics pipeline from all configurations\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanPipeline.cpp:155\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanPipeline.h (TODO 3 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Conclusion\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 3.3\n"
        "========================================\n"
    );
}
