#include "Rendering/ForwardPass.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Framework/Camera.h"
#include "Rendering/Mesh.h"
#include "Rendering/SimpleMaterial.h"

ForwardPass::~ForwardPass() {
    cleanup();
}

void ForwardPass::initialize(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D extent
) {
    m_device = device;
    // Phase 1: ForwardPass不需要额外初始化
    // Later: 可能需要创建descriptor sets等
}

void ForwardPass::execute(VkCommandBuffer cmd, ECS& ecs) {
    if (!m_camera) return;

    // 获取相机的View和Projection矩阵
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjectionMatrix();
    glm::mat4 vp = proj * view;

    // 遍历所有有Mesh和Material的实体
    auto entities = ecs.entitiesWith<MeshComponent, MaterialComponent, TransformComponent>();

    for (Entity entity : entities) {
        auto* meshComp = ecs.getComponent<MeshComponent>(entity);
        auto* materialComp = ecs.getComponent<MaterialComponent>(entity);
        auto* transformComp = ecs.getComponent<TransformComponent>(entity);

        if (!meshComp->mesh || !materialComp->material) continue;

        // 计算MVP矩阵
        glm::mat4 model = transformComp->transform;
        glm::mat4 mvp = vp * model;

        // 绑定材质
        materialComp->material->bind(cmd);

        // 设置MVP（通过push constants）
        // ASSUMPTION: 材质支持setMVP（SimpleMaterial有此方法）
        auto* simpleMaterial = dynamic_cast<SimpleMaterial*>(materialComp->material);
        if (simpleMaterial) {
            simpleMaterial->setMVP(cmd, mvp);
        }

        // 绘制网格
        meshComp->mesh->draw(cmd);
    }
}

void ForwardPass::cleanup() {
    // Phase 1: 无需清理
}
