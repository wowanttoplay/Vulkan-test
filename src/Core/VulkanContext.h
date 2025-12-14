#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <memory>

// Forward declarations
class Window;
class VulkanSwapchain;

/**
 * ============================================================================
 * VULKAN LEARNING MODULE: VulkanContext
 * ============================================================================
 *
 * This file is YOUR LEARNING FOCUS for Phase 1, Step 1.
 *
 * WHAT YOU WILL LEARN:
 * 1. Vulkan Instance creation
 * 2. Validation layers setup
 * 3. Physical device selection
 * 4. Logical device creation
 * 5. Queue family management
 *
 * HOW THIS WORKS:
 * - Functions marked with [TODO] need to be implemented by YOU
 * - Functions without [TODO] are helper functions (already implemented)
 * - Read the comments carefully - they explain Vulkan concepts
 * - Refer to docs/PHASE1_GUIDE.md for detailed instructions
 *
 * ESTIMATED TIME: 2-4 hours
 * ============================================================================
 */

class VulkanContext {
public:
    VulkanContext();
    ~VulkanContext();

    // Main initialization function
    void initialize(Window* window, bool enableValidation = true);
    void cleanup();

    // Getters
    VkInstance getInstance() const { return m_instance; }
    VkPhysicalDevice getPhysicalDevice() const { return m_physicalDevice; }
    VkDevice getDevice() const { return m_device; }
    VkSurfaceKHR getSurface() const { return m_surface; }
    VkQueue getGraphicsQueue() const { return m_graphicsQueue; }
    VkQueue getPresentQueue() const { return m_presentQueue; }
    VulkanSwapchain* getSwapchain() const { return m_swapchain.get(); }

    // Queue family indices
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices getQueueFamilies() const { return m_queueFamilies; }

private:
    // ========================================================================
    // [TODO 1] CREATE VULKAN INSTANCE
    // ========================================================================
    // CONCEPT: VkInstance is the connection between your app and Vulkan
    //
    // YOU NEED TO:
    // 1. Fill in VkApplicationInfo (app name, version, etc.)
    // 2. Fill in VkInstanceCreateInfo (extensions, layers)
    // 3. Call vkCreateInstance()
    //
    // HINT: Required extensions are returned by getRequiredExtensions()
    // HINT: Validation layers are in getValidationLayers()
    //
    // VALIDATION: After implementing, you should see Vulkan instance created
    //             with no errors in the console.
    // ========================================================================
    void createInstance();

    // ========================================================================
    // [TODO 2] SETUP VALIDATION LAYERS
    // ========================================================================
    // CONCEPT: Validation layers catch errors during development
    //
    // YOU NEED TO:
    // 1. Create VkDebugUtilsMessengerCreateInfoEXT
    // 2. Call vkCreateDebugUtilsMessengerEXT()
    //
    // HINT: Use debugCallback() as the callback function
    //
    // VALIDATION: You should see validation messages in console when errors occur
    // ========================================================================
    void setupDebugMessenger();

    // ========================================================================
    // [TODO 3] CREATE SURFACE
    // ========================================================================
    // CONCEPT: VkSurfaceKHR is the interface to the window system
    //
    // YOU NEED TO:
    // 1. Use GLFW's glfwCreateWindowSurface() helper
    //
    // HINT: The window pointer is passed to initialize()
    //
    // VALIDATION: Surface should be created successfully
    // ========================================================================
    void createSurface(Window* window);

    // ========================================================================
    // [TODO 4] PICK PHYSICAL DEVICE
    // ========================================================================
    // CONCEPT: Physical device = GPU. Need to choose the best one.
    //
    // YOU NEED TO:
    // 1. Enumerate all physical devices (vkEnumeratePhysicalDevices)
    // 2. Rate each device based on features/properties
    // 3. Select the highest-rated device
    //
    // HINT: Use isDeviceSuitable() to check if device is usable
    // HINT: Use rateDeviceSuitability() to score devices
    //
    // VALIDATION: Should select your GPU (discrete > integrated)
    // ========================================================================
    void pickPhysicalDevice();

    // ========================================================================
    // [TODO 5] CREATE LOGICAL DEVICE
    // ========================================================================
    // CONCEPT: Logical device is your interface to the physical device
    //
    // YOU NEED TO:
    // 1. Specify queue families to create
    // 2. Enable device extensions (swapchain)
    // 3. Call vkCreateDevice()
    // 4. Retrieve queue handles (vkGetDeviceQueue)
    //
    // HINT: Queue families are in m_queueFamilies
    // HINT: Required extensions: VK_KHR_SWAPCHAIN_EXTENSION_NAME
    //
    // VALIDATION: Device created, queues retrieved successfully
    // ========================================================================
    void createLogicalDevice();

    // ========================================================================
    // HELPER FUNCTIONS (Already implemented for you)
    // ========================================================================

    // Find queue families that support graphics and present
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    // Check if device has required features
    bool isDeviceSuitable(VkPhysicalDevice device);

    // Rate device based on type and features (higher = better)
    int rateDeviceSuitability(VkPhysicalDevice device);

    // Get required Vulkan extensions (GLFW + debug utils)
    std::vector<const char*> getRequiredExtensions() const;

    // Get validation layer names
    std::vector<const char*> getValidationLayers() const;

    // Check if validation layers are available
    bool checkValidationLayerSupport() const;

    // Debug callback for validation layers
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

    // ========================================================================
    // MEMBER VARIABLES
    // ========================================================================

    VkInstance m_instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
    VkSurfaceKHR m_surface = VK_NULL_HANDLE;

    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device = VK_NULL_HANDLE;

    VkQueue m_graphicsQueue = VK_NULL_HANDLE;
    VkQueue m_presentQueue = VK_NULL_HANDLE;

    QueueFamilyIndices m_queueFamilies;

    Window* m_window = nullptr;
    bool m_enableValidation = true;

    std::unique_ptr<VulkanSwapchain> m_swapchain;
};
