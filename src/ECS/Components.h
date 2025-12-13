#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

// Forward declarations
class Mesh;
class Material;

/**
 * @brief Transform component - Position, Rotation, Scale
 *
 * Stores the transformation matrix for an entity.
 * You can extend this to store position/rotation/scale separately if needed.
 */
struct TransformComponent {
    glm::mat4 transform = glm::mat4(1.0f);

    // Helper functions to build transform from components
    static glm::mat4 fromPositionRotationScale(
        const glm::vec3& position,
        const glm::vec3& rotation,  // Euler angles in radians
        const glm::vec3& scale
    ) {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, position);
        mat = glm::rotate(mat, rotation.x, glm::vec3(1, 0, 0));
        mat = glm::rotate(mat, rotation.y, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, rotation.z, glm::vec3(0, 0, 1));
        mat = glm::scale(mat, scale);
        return mat;
    }
};

/**
 * @brief Mesh component - References a mesh to render
 *
 * The mesh itself is managed separately and shared between entities.
 * This component just holds a pointer to it.
 */
struct MeshComponent {
    Mesh* mesh = nullptr;
};

/**
 * @brief Material component - References a material for rendering
 *
 * Materials are polymorphic (PBR, Water, Glass, etc.) and managed separately.
 */
struct MaterialComponent {
    Material* material = nullptr;
};

/**
 * @brief Pickable component - Allows entity to be selected
 *
 * Used by the picking system to identify selectable objects.
 * pickID is a unique identifier for color-based picking (Phase 2).
 */
struct PickableComponent {
    uint32_t pickID = 0;
    bool isSelected = false;
};

/**
 * @brief Name component - Human-readable name for UI
 *
 * Useful for scene hierarchy display.
 */
struct NameComponent {
    std::string name = "Entity";
};

/**
 * @brief AABB component - Axis-Aligned Bounding Box
 *
 * Used for frustum culling and ray-casting picking.
 * You'll implement this in Phase 2.
 */
struct AABBComponent {
    glm::vec3 min = glm::vec3(-0.5f);
    glm::vec3 max = glm::vec3(0.5f);

    glm::vec3 getCenter() const {
        return (min + max) * 0.5f;
    }

    glm::vec3 getExtents() const {
        return (max - min) * 0.5f;
    }
};

// Future components you can add:
// - struct LightComponent { ... };
// - struct CameraComponent { ... };
// - struct PhysicsComponent { ... };
// - struct AnimationComponent { ... };
// Just define the struct and use it with ECS!
