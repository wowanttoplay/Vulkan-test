#pragma once

#include <vulkan/vulkan.h>

/**
 * @brief 材质接口
 *
 * 设计哲学：
 * - 材质是可扩展的抽象
 * - 每个材质类型有自己的着色器和参数
 * - 通过虚函数实现多态
 *
 * 扩展方式：
 * 1. 创建新的材质类，继承Material
 * 2. 实现bind()和renderUI()
 * 3. 在构造函数中创建自己的pipeline
 *
 * Example:
 *   class WaterMaterial : public Material {
 *   public:
 *       WaterMaterial(...) {
 *           // 创建水材质的pipeline
 *       }
 *       void bind(VkCommandBuffer cmd) override {
 *           // 绑定水材质的pipeline和descriptors
 *       }
 *       void renderUI() override {
 *           // ImGui controls for water parameters
 *       }
 *   };
 */
class Material {
public:
    virtual ~Material() = default;

    /**
     * @brief 绑定材质的pipeline和descriptors
     *
     * 在绘制前调用，设置渲染状态
     */
    virtual void bind(VkCommandBuffer commandBuffer) = 0;

    /**
     * @brief 渲染ImGui控件（材质参数编辑）
     *
     * 在UI窗口中调用，允许用户调整材质参数
     */
    virtual void renderUI() = 0;

    /**
     * @brief 清理资源
     */
    virtual void cleanup() = 0;

    /**
     * @brief 获取材质名称（用于UI显示）
     */
    virtual const char* getName() const = 0;
};
