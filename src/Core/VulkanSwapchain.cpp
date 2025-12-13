#include "Core/VulkanSwapchain.h"
#include "Framework/Window.h"
#include <stdexcept>

VulkanSwapchain::~VulkanSwapchain() {
    cleanup();
}

void VulkanSwapchain::initialize(
    VkPhysicalDevice physicalDevice,
    VkDevice device,
    VkSurfaceKHR surface,
    Window* window
) {
    m_physicalDevice = physicalDevice;
    m_device = device;
    m_surface = surface;
    m_window = window;

    createSwapchain();
    createImageViews();
}

void VulkanSwapchain::cleanup() {
    for (auto imageView : m_imageViews) {
        vkDestroyImageView(m_device, imageView, nullptr);
    }
    m_imageViews.clear();

    if (m_swapchain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
        m_swapchain = VK_NULL_HANDLE;
    }
}

void VulkanSwapchain::recreate() {
    cleanup();
    createSwapchain();
    createImageViews();
}

// ============================================================================
// [TODO 1] QUERY SWAPCHAIN SUPPORT
// ============================================================================
VulkanSwapchain::SwapchainSupportDetails VulkanSwapchain::querySwapchainSupport(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  querySwapchainSupport() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Query swapchain capabilities, formats, and present modes\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:42\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 1 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.1\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 2] CHOOSE SWAP SURFACE FORMAT
// ============================================================================
VkSurfaceFormatKHR VulkanSwapchain::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  chooseSwapSurfaceFormat() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Choose the best surface format (color space)\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:63\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 2 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.2\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 3] CHOOSE SWAP PRESENT MODE
// ============================================================================
VkPresentModeKHR VulkanSwapchain::chooseSwapPresentMode(
    const std::vector<VkPresentModeKHR>& availablePresentModes
) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  chooseSwapPresentMode() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Choose the best present mode (FIFO, Mailbox, etc.)\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:84\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 3 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.3\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 4] CHOOSE SWAP EXTENT
// ============================================================================
VkExtent2D VulkanSwapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  chooseSwapExtent() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Choose swapchain image resolution\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:105\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 4 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.4\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 5] CREATE SWAPCHAIN
// ============================================================================
void VulkanSwapchain::createSwapchain() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createSwapchain() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Create VkSwapchainKHR object\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:126\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 5 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.5\n"
        "========================================\n"
    );
}

// ============================================================================
// [TODO 6] CREATE IMAGE VIEWS
// ============================================================================
void VulkanSwapchain::createImageViews() {
    throw std::runtime_error(
        "\n"
        "========================================\n"
        "TODO NOT IMPLEMENTED:\n"
        "  createImageViews() in VulkanSwapchain.cpp\n"
        "\n"
        "TASK:\n"
        "  Create image views for swapchain images\n"
        "\n"
        "LOCATION:\n"
        "  src/Core/VulkanSwapchain.cpp:147\n"
        "\n"
        "REFERENCE:\n"
        "  - VulkanSwapchain.h (TODO 6 comments)\n"
        "  - https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Image_views\n"
        "\n"
        "GUIDE:\n"
        "  docs/PHASE1_GUIDE.md - Step 2.6\n"
        "========================================\n"
    );
}
