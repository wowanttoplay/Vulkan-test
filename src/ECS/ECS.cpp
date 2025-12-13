#include "ECS/ECS.h"
#include <algorithm>

ECS::ECS() {
}

ECS::~ECS() {
    // Clean up all components
    for (auto& [entity, components] : m_components) {
        for (auto& [typeID, componentPtr] : components) {
            // We don't know the actual type here, so we can't properly delete
            // In a production system, you'd store destructors alongside the data
            // For now, this is a known limitation - components leak on ECS destruction
            // (but the OS will clean up when the program exits)
        }
    }
}

Entity ECS::createEntity() {
    Entity newEntity = m_nextEntityID++;
    m_entities.push_back(newEntity);
    return newEntity;
}

void ECS::destroyEntity(Entity entity) {
    // Remove from entity list
    auto it = std::find(m_entities.begin(), m_entities.end(), entity);
    if (it != m_entities.end()) {
        m_entities.erase(it);
    }

    // Clean up all components for this entity
    auto compIt = m_components.find(entity);
    if (compIt != m_components.end()) {
        // Note: Proper deletion would require storing type information
        // This is simplified for the learning framework
        m_components.erase(compIt);
    }

    // Remove from entity components tracking
    m_entityComponents.erase(entity);
}

bool ECS::isEntityValid(Entity entity) const {
    return std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end();
}
