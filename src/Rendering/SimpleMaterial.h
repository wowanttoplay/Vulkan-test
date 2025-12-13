#pragma once

#include "Rendering/Material.h"
#include <glm/glm.hpp>

/**
 * @brief 简单材质 - 第一个具体材质实现
 *
 * 功能：
 * - 纯色渲染（顶点颜色）
 * - 简单的MVP变换
 * - 用于Phase 1学习
 *
 * Later：添加PBRMaterial, WaterMaterial等
 */
class SimpleMaterial : public Material {
public:
    SimpleMaterial();
    ~SimpleMaterial() override;

    void initialize(
        VkDevice device,
        VkRenderPass renderPass,
        VkExtent2D extent
    );

    void bind(VkCommandBuffer commandBuffer) override;
    void renderUI() override;
    void cleanup() override;
    const char* getName() const override { return "Simple Material"; }

    // 设置变换矩阵（通过push constants）
    void setMVP(VkCommandBuffer commandBuffer, const glm::mat4& mvp);

    VkPipeline getPipeline() const { return m_pipeline; }
    VkPipelineLayout getPipelineLayout() const { return m_pipelineLayout; }

private:
    VkDevice m_device = VK_NULL_HANDLE;
    VkPipeline m_pipeline = VK_NULL_HANDLE;
    VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

    // 材质参数
    glm::vec3 m_color = glm::vec3(1.0f);
};
