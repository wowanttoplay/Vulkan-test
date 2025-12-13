#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

// Entity is just a unique ID
using Entity = uint32_t;
using ComponentTypeID = std::type_index;

/**
 * @brief Simple Entity-Component-System (ECS) implementation
 *
 * This is a minimal ECS designed for easy extension. You can:
 * - Add new component types by just defining structs
 * - Add new systems by creating classes that operate on components
 * - Query entities by component types
 *
 * The implementation uses a simple map-based storage. This can be
 * optimized later to use archetype-based or SoA storage if needed.
 */
class ECS {
public:
    ECS();
    ~ECS();

    // Entity management
    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isEntityValid(Entity entity) const;

    // Component management
    template<typename T>
    void addComponent(Entity entity, const T& component);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T* getComponent(Entity entity);

    template<typename T>
    const T* getComponent(Entity entity) const;

    template<typename T>
    bool hasComponent(Entity entity) const;

    // Query entities with specific components
    template<typename T>
    std::vector<Entity> entitiesWith() const;

    template<typename T1, typename T2>
    std::vector<Entity> entitiesWith() const;

    template<typename T1, typename T2, typename T3>
    std::vector<Entity> entitiesWith() const;

    // Get all entities
    const std::vector<Entity>& getAllEntities() const { return m_entities; }

private:
    uint32_t m_nextEntityID = 1;
    std::vector<Entity> m_entities;

    // Component storage: Entity -> (ComponentType -> Component*)
    std::unordered_map<Entity, std::unordered_map<ComponentTypeID, void*>> m_components;

    // Track which component types an entity has
    std::unordered_map<Entity, std::vector<ComponentTypeID>> m_entityComponents;
};

// Template implementations

template<typename T>
void ECS::addComponent(Entity entity, const T& component) {
    ComponentTypeID typeID = std::type_index(typeid(T));

    // Allocate and copy component
    T* componentPtr = new T(component);
    m_components[entity][typeID] = componentPtr;
    m_entityComponents[entity].push_back(typeID);
}

template<typename T>
void ECS::removeComponent(Entity entity) {
    ComponentTypeID typeID = std::type_index(typeid(T));

    auto entityIt = m_components.find(entity);
    if (entityIt != m_components.end()) {
        auto compIt = entityIt->second.find(typeID);
        if (compIt != entityIt->second.end()) {
            delete static_cast<T*>(compIt->second);
            entityIt->second.erase(compIt);
        }
    }

    // Remove from entity component list
    auto& compList = m_entityComponents[entity];
    compList.erase(std::remove(compList.begin(), compList.end(), typeID), compList.end());
}

template<typename T>
T* ECS::getComponent(Entity entity) {
    ComponentTypeID typeID = std::type_index(typeid(T));

    auto entityIt = m_components.find(entity);
    if (entityIt != m_components.end()) {
        auto compIt = entityIt->second.find(typeID);
        if (compIt != entityIt->second.end()) {
            return static_cast<T*>(compIt->second);
        }
    }
    return nullptr;
}

template<typename T>
const T* ECS::getComponent(Entity entity) const {
    ComponentTypeID typeID = std::type_index(typeid(T));

    auto entityIt = m_components.find(entity);
    if (entityIt != m_components.end()) {
        auto compIt = entityIt->second.find(typeID);
        if (compIt != entityIt->second.end()) {
            return static_cast<const T*>(compIt->second);
        }
    }
    return nullptr;
}

template<typename T>
bool ECS::hasComponent(Entity entity) const {
    ComponentTypeID typeID = std::type_index(typeid(T));

    auto entityIt = m_components.find(entity);
    if (entityIt != m_components.end()) {
        return entityIt->second.find(typeID) != entityIt->second.end();
    }
    return false;
}

template<typename T>
std::vector<Entity> ECS::entitiesWith() const {
    std::vector<Entity> result;
    for (Entity entity : m_entities) {
        if (hasComponent<T>(entity)) {
            result.push_back(entity);
        }
    }
    return result;
}

template<typename T1, typename T2>
std::vector<Entity> ECS::entitiesWith() const {
    std::vector<Entity> result;
    for (Entity entity : m_entities) {
        if (hasComponent<T1>(entity) && hasComponent<T2>(entity)) {
            result.push_back(entity);
        }
    }
    return result;
}

template<typename T1, typename T2, typename T3>
std::vector<Entity> ECS::entitiesWith() const {
    std::vector<Entity> result;
    for (Entity entity : m_entities) {
        if (hasComponent<T1>(entity) && hasComponent<T2>(entity) && hasComponent<T3>(entity)) {
            result.push_back(entity);
        }
    }
    return result;
}
