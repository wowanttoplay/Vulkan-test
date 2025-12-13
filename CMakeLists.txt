cmake_minimum_required(VERSION 3.20)
project(VulkanSandbox VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan SDK
find_package(Vulkan REQUIRED)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Options
option(ENABLE_VALIDATION "Enable Vulkan validation layers" ON)

# ============================================================================
# External Dependencies
# ============================================================================

# GLFW - Window management
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLM - Math library (header-only)
add_subdirectory(external/glm)

# VMA - Vulkan Memory Allocator (header-only)
add_library(vma INTERFACE)
target_include_directories(vma INTERFACE external/vma/include)

# ImGui - UI library
add_subdirectory(external/imgui_cmake)

# ============================================================================
# Source Files
# ============================================================================
set(CORE_SOURCES
    # Vulkan Core (YOU WILL IMPLEMENT THESE)
    src/Core/VulkanContext.cpp
    src/Core/VulkanSwapchain.cpp
    src/Core/VulkanPipeline.cpp
    src/Core/VulkanBuffer.cpp
    src/Core/VulkanImage.cpp

    # ECS System (ALREADY IMPLEMENTED)
    src/ECS/ECS.cpp

    # Framework (ALREADY IMPLEMENTED)
    src/Framework/Application.cpp
    src/Framework/Window.cpp
    src/Framework/Camera.cpp
    src/Framework/Input.cpp

    # Rendering System
    src/Rendering/Renderer.cpp
    src/Rendering/ForwardPass.cpp
    src/Rendering/SimpleMaterial.cpp
    src/Rendering/Mesh.cpp
)

add_executable(VulkanSandbox
    src/main.cpp
    ${CORE_SOURCES}
)

# ============================================================================
# Include Directories
# ============================================================================
target_include_directories(VulkanSandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${Vulkan_INCLUDE_DIRS}
)

# ============================================================================
# Link Libraries
# ============================================================================
target_link_libraries(VulkanSandbox PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
    vma
    imgui
)

if(ENABLE_VALIDATION)
    target_compile_definitions(VulkanSandbox PRIVATE ENABLE_VALIDATION_LAYERS)
endif()

# Shader compilation
add_custom_target(CompileShaders
    COMMAND ${CMAKE_COMMAND} -E echo "Compiling shaders..."
    COMMAND ${CMAKE_SOURCE_DIR}/tools/compile_shaders.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_dependencies(VulkanSandbox CompileShaders)

# Copy shaders to output directory
add_custom_command(TARGET VulkanSandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders/compiled
    $<TARGET_FILE_DIR:VulkanSandbox>/shaders
)
