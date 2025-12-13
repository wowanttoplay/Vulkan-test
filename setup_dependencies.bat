@echo off
REM ============================================================================
REM External Dependencies Setup Script
REM ============================================================================
REM
REM This script will download and configure all external dependencies
REM for the Vulkan Learning project.
REM
REM Dependencies:
REM 1. GLFW - Window management
REM 2. GLM - Math library
REM 3. VMA - Vulkan Memory Allocator
REM 4. ImGui - UI library
REM
REM Requirements:
REM - Git must be installed and in PATH
REM - Vulkan SDK must be installed separately
REM
REM ============================================================================

echo ========================================
echo Setting up external dependencies...
echo ========================================
echo.

REM Create external directory
if not exist external mkdir external
cd external

REM ============================================================================
REM 1. GLFW (Window Management)
REM ============================================================================
echo [1/4] Setting up GLFW...
if not exist glfw (
    echo   Cloning GLFW from GitHub...
    git clone https://github.com/glfw/glfw.git glfw
    cd glfw
    git checkout 3.4
    cd ..
    echo   GLFW cloned successfully!
) else (
    echo   GLFW already exists, skipping...
)
echo.

REM ============================================================================
REM 2. GLM (Math Library)
REM ============================================================================
echo [2/4] Setting up GLM...
if not exist glm (
    echo   Cloning GLM from GitHub...
    git clone https://github.com/g-truc/glm.git glm
    cd glm
    git checkout 0.9.9.8
    cd ..
    echo   GLM cloned successfully!
) else (
    echo   GLM already exists, skipping...
)
echo.

REM ============================================================================
REM 3. VMA (Vulkan Memory Allocator)
REM ============================================================================
echo [3/4] Setting up VMA...
if not exist vma (
    echo   Cloning VMA from GitHub...
    git clone https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git vma
    cd vma
    git checkout v3.0.1
    cd ..
    echo   VMA cloned successfully!
) else (
    echo   VMA already exists, skipping...
)
echo.

REM ============================================================================
REM 4. ImGui (UI Library)
REM ============================================================================
echo [4/4] Setting up ImGui...
if not exist imgui (
    echo   Cloning ImGui from GitHub...
    git clone https://github.com/ocornut/imgui.git imgui
    cd imgui
    git checkout v1.90.1
    cd ..
    echo   ImGui cloned successfully!
) else (
    echo   ImGui already exists, skipping...
)
echo.

cd ..

echo ========================================
echo Dependencies setup complete!
echo ========================================
echo.
echo External libraries installed:
echo   - GLFW (3.4)
echo   - GLM (0.9.9.8)
echo   - VMA (3.0.1)
echo   - ImGui (1.90.1)
echo.
echo IMPORTANT: Vulkan SDK must be installed separately!
echo Download from: https://vulkan.lunarg.com/
echo.
echo Next steps:
echo   1. Install Vulkan SDK if not already installed
echo   2. Run: mkdir build ^&^& cd build
echo   3. Run: cmake ..
echo   4. Run: cmake --build . --config Debug
echo.
pause
