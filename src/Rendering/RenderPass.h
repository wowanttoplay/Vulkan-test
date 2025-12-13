#pragma once

#include <vulkan/vulkan.h>

class ECS;

/**
 * @brief 渲染Pass接口
 *
 * 设计哲学：
 * - 渲染系统由多个Pass组成
 * - 每个Pass负责一个渲染阶段
 * - Pass可以独立添加、移除、重新排序
 *
 * 常见Pass类型：
 * - ForwardPass：前向渲染（不透明物体）
 * - ShadowPass：阴影贴图生成
 * - TransparentPass：透明物体渲染
 * - PostProcessPass：后处理效果
 * - SSAOPass：屏幕空间环境光遮蔽
 *
 * 扩展方式：
 * 1. 创建新的Pass类，继承IRenderPass
 * 2. 实现execute()方法
 * 3. 在Renderer中注册Pass
 *
 * Example:
 *   class ShadowPass : public IRenderPass {
 *   public:
 *       void execute(VkCommandBuffer cmd, ECS& ecs) override {
 *           // 1. 绑定shadow framebuffer
 *           // 2. 渲染深度
 *           // 3. 存储shadow map
 *       }
 *   };
 */
class IRenderPass {
public:
    virtual ~IRenderPass() = default;

    /**
     * @brief 执行渲染Pass
     *
     * @param cmd Vulkan命令缓冲区
     * @param ecs ECS实例（访问entities和components）
     */
    virtual void execute(VkCommandBuffer cmd, ECS& ecs) = 0;

    /**
     * @brief 清理资源
     */
    virtual void cleanup() = 0;
};
