#pragma once

#include "Rendering/RenderPass.h"
#include <vulkan/vulkan.h>

class Camera;

/**
 * @brief 前向渲染Pass - 第一个具体Pass实现
 *
 * 功能：
 * - 渲染所有不透明物体
 * - 使用SimpleMaterial
 * - Phase 1的主要渲染Pass
 *
 * Later：添加ShadowPass, TransparentPass等
 */
class ForwardPass : public IRenderPass {
public:
    ForwardPass() = default;
    ~ForwardPass() override;

    void initialize(
        VkDevice device,
        VkRenderPass renderPass,
        VkExtent2D extent
    );

    void execute(VkCommandBuffer cmd, ECS& ecs) override;
    void cleanup() override;

    // 设置相机（用于MVP计算）
    void setCamera(Camera* camera) { m_camera = camera; }

private:
    VkDevice m_device = VK_NULL_HANDLE;
    Camera* m_camera = nullptr;
};
