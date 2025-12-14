@echo off
REM ============================================================================
REM Run Vulkan Project
REM ============================================================================

echo ========================================
echo Running Vulkan Learning Project
echo ========================================
echo.

if not exist build\bin\Debug\VulkanSandbox.exe (
    echo [ERROR] VulkanSandbox.exe not found!
    echo.
    echo Please build the project first:
    echo   build_project.bat
    echo.
    pause
    exit /b 1
)

cd build\bin\Debug

echo Starting application...
echo.
echo Controls:
echo   WASD - Move camera
echo   Mouse Right Click - Look around
echo   E/Space - Move up
echo   Q/Shift - Move down
echo   ESC - Exit
echo.
echo ========================================
echo.

VulkanSandbox.exe

echo.
echo ========================================
echo Application closed
echo ========================================
echo.

cd ..\..\..
pause
