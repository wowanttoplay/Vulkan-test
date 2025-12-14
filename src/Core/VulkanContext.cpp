#include "Core/VulkanContext.h"
#include "Core/VulkanSwapchain.h"
#include "Framework/Window.h"
#include <stdexcept>
#include <iostream>

VulkanContext::VulkanContext() = default;

VulkanContext::~VulkanContext() {
    cleanup();
}

void VulkanContext::initialize(Window* window, bool enableValidation) {
    m_window = window;
    m_enableValidation = enableValidation;

    std::cout << "Initializing Vulkan Context..." << std::endl;

    // TODO: Implement these 5 functions in order
    createInstance();
    setupDebugMessenger();
    createSurface(m_window);
    pickPhysicalDevice();
    createLogicalDevice();

    // Create swapchain
    m_swapchain = std::make_unique<VulkanSwapchain>();
    m_swapchain->initialize(m_physicalDevice, m_device, m_surface, m_window);

    std::cout << "Vulkan Context initialized successfully!" << std::endl;
}

void VulkanContext::cleanup() {
    // Cleanup swapchain first
    if (m_swapchain) {
        m_swapchain->cleanup();
        m_swapchain.reset();
    }

    if (m_device != VK_NULL_HANDLE) {
        vkDestroyDevice(m_device, nullptr);
        m_device = VK_NULL_HANDLE;
    }

    if (m_enableValidation && m_debugMessenger != VK_NULL_HANDLE) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            m_instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(m_instance, m_debugMessenger, nullptr);
        }
        m_debugMessenger = VK_NULL_HANDLE;
    }

    if (m_surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
        m_surface = VK_NULL_HANDLE;
    }

    if (m_instance != VK_NULL_HANDLE) {
        vkDestroyInstance(m_instance, nullptr);
        m_instance = VK_NULL_HANDLE;
    }
}

// ============================================================================
// [TODO 1] CREATE VULKAN INSTANCE
// ============================================================================
void VulkanContext::createInstance() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createInstance() in VulkanContext.cpp\n"
        "\n"
        "TASK:\n"
        "  Implement Vulkan instance creation\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanContext.cpp:50\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanContext.h (TODO 1 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 1.1\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 2] SETUP DEBUG MESSENGER
// ============================================================================
void VulkanContext::setupDebugMessenger() {
    if (!m_enableValidation) return;

    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  setupDebugMessenger() in VulkanContext.cpp\n"
        "\n"
        "TASK:\n"
        "  Setup validation layer debug callback\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanContext.cpp:69\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanContext.h (TODO 2 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 1.2\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 3] CREATE SURFACE
// ============================================================================
void VulkanContext::createSurface(Window* window) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createSurface() in VulkanContext.cpp\n"
        "\n"
        "TASK:\n"
        "  Create window surface for rendering\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanContext.cpp:90\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanContext.h (TODO 3 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 1.3\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 4] PICK PHYSICAL DEVICE
// ============================================================================
void VulkanContext::pickPhysicalDevice() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  pickPhysicalDevice() in VulkanContext.cpp\n"
        "\n"
        "TASK:\n"
        "  Select a suitable GPU\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanContext.cpp:111\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanContext.h (TODO 4 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 1.4\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 5] CREATE LOGICAL DEVICE
// ============================================================================
void VulkanContext::createLogicalDevice() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createLogicalDevice() in VulkanContext.cpp\n"
        "\n"
        "TASK:\n"
        "  Create logical device and get queue handles\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanContext.cpp:132\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanContext.h (TODO 5 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Logical_device_and_queues\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 1.5\n"
        "========================================\n"
    );
}

// ============================================================================
// Helper Functions
// ============================================================================

bool VulkanContext::checkValidationLayerSupport() const {
    // TODO: Implement validation layer check
    // This is needed for setupDebugMessenger
    return true;  // Placeholder
}

std::vector<const char*> VulkanContext::getRequiredExtensions() const {
    // TODO: Implement extension enumeration
    // This is needed for createInstance
    return {};  // Placeholder
}

VulkanContext::QueueFamilyIndices VulkanContext::findQueueFamilies(VkPhysicalDevice device) {
    // TODO: Implement queue family search
    // This is needed for pickPhysicalDevice and createLogicalDevice
    return {};  // Placeholder
}

bool VulkanContext::isDeviceSuitable(VkPhysicalDevice device) {
    // TODO: Implement device suitability check
    // This is needed for pickPhysicalDevice
    return false;  // Placeholder
}
