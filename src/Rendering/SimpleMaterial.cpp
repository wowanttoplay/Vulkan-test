#include "Rendering/SimpleMaterial.h"
#include "Core/VulkanPipeline.h"
#include "Rendering/Mesh.h"
#include <imgui.h>

SimpleMaterial::SimpleMaterial() {
}

SimpleMaterial::~SimpleMaterial() {
    cleanup();
}

void SimpleMaterial::initialize(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D extent
) {
    m_device = device;

    // 创建管线布局（使用push constants传递MVP）
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(glm::mat4);  // MVP矩阵

    VkPipelineLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layoutInfo.pushConstantRangeCount = 1;
    layoutInfo.pPushConstantRanges = &pushConstantRange;
    layoutInfo.setLayoutCount = 0;  // Phase 1不使用descriptor sets
    layoutInfo.pSetLayouts = nullptr;

    if (vkCreatePipelineLayout(m_device, &layoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout!");
    }

    // 创建图形管线
    VulkanPipelineBuilder builder(m_device);

    auto bindings = Vertex::getBindingDescription();
    auto attributes = Vertex::getAttributeDescriptions();

    m_pipeline = builder
        .setShaders("shaders/compiled/simple.vert.spv", "shaders/compiled/simple.frag.spv")
        .setVertexInput({bindings}, attributes)
        .setInputAssembly(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
        .setViewport(extent)
        .setRasterizer(VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_COUNTER_CLOCKWISE)
        .setMultisampling(VK_SAMPLE_COUNT_1_BIT)
        .setDepthStencil(VK_TRUE, VK_TRUE, VK_COMPARE_OP_LESS)
        .setColorBlending(VK_FALSE)
        .setRenderPass(renderPass, 0)
        .build();
}

void SimpleMaterial::bind(VkCommandBuffer commandBuffer) {
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
}

void SimpleMaterial::renderUI() {
    ImGui::Text("Simple Material");
    ImGui::ColorEdit3("Color", &m_color.x);
    ImGui::Separator();
}

void SimpleMaterial::setMVP(VkCommandBuffer commandBuffer, const glm::mat4& mvp) {
    vkCmdPushConstants(
        commandBuffer,
        m_pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT,
        0,
        sizeof(glm::mat4),
        &mvp
    );
}

void SimpleMaterial::cleanup() {
    if (m_pipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(m_device, m_pipeline, nullptr);
        m_pipeline = VK_NULL_HANDLE;
    }
    if (m_pipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
        m_pipelineLayout = VK_NULL_HANDLE;
    }
}
