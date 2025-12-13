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

# External dependencies (to be populated)
# For now, we'll add these as submodules or manually
# - GLFW for windowing
# - GLM for math
# - Dear ImGui for UI
# - VMA for memory management

# Core library (will be built incrementally)
set(CORE_SOURCES
    # Vulkan Core (YOU WILL IMPLEMENT THESE)
    src/Core/VulkanContext.cpp
    src/Core/VulkanSwapchain.cpp
    src/Core/VulkanPipeline.cpp
    src/Core/VulkanBuffer.cpp
    src/Core/VulkanImage.cpp

    # ECS System (ALREADY IMPLEMENTED FOR YOU)
    src/ECS/ECS.cpp
    src/ECS/ComponentStorage.cpp

    # Framework (ALREADY IMPLEMENTED FOR YOU)
    src/Framework/Application.cpp
    src/Framework/Window.cpp
    src/Framework/Camera.cpp
    src/Framework/Input.cpp

    # Rendering System
    src/Rendering/Renderer.cpp
    src/Rendering/ForwardPass.cpp
    src/Rendering/SimpleMaterial.cpp
    src/Rendering/Mesh.cpp

    # UI (ALREADY IMPLEMENTED FOR YOU)
    src/UI/SceneHierarchy.cpp
)

add_executable(VulkanSandbox
    src/main.cpp
    ${CORE_SOURCES}
)

target_include_directories(VulkanSandbox PRIVATE
    src
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(VulkanSandbox PRIVATE
    Vulkan::Vulkan
    # GLFW will be added
    # GLM will be added
    # ImGui will be added
    # VMA will be added
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
