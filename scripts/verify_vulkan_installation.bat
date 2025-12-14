@echo off
REM ============================================================================
REM Vulkan SDK Installation Verification Script
REM ============================================================================

setlocal enabledelayedexpansion

echo ========================================
echo Vulkan SDK Installation Verification
echo ========================================
echo.

set ERRORS=0

REM ============================================================================
REM Check 1: VULKAN_SDK environment variable
REM ============================================================================
echo [1/5] Checking VULKAN_SDK environment variable...

if defined VULKAN_SDK (
    echo [OK] VULKAN_SDK found
    echo      Path: %VULKAN_SDK%

    REM Check if directory exists
    if exist "%VULKAN_SDK%" (
        echo [OK] Directory exists
    ) else (
        echo [ERROR] Directory does not exist!
        set /a ERRORS+=1
    )
) else (
    echo [ERROR] VULKAN_SDK environment variable not found!
    echo.
    echo SOLUTION:
    echo   1. Reinstall Vulkan SDK and check "Add to PATH"
    echo   2. OR manually set VULKAN_SDK environment variable
    echo   3. See install_vulkan_sdk.md for detailed instructions
    set /a ERRORS+=1
)
echo.

REM ============================================================================
REM Check 2: glslc shader compiler
REM ============================================================================
echo [2/5] Checking glslc shader compiler...

where glslc >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] glslc found in PATH
    for /f "tokens=*" %%i in ('glslc --version 2^>^&1') do (
        echo      Version: %%i
        goto :glslc_version_found
    )
    :glslc_version_found
) else (
    echo [ERROR] glslc not found in PATH!
    echo.
    echo SOLUTION:
    echo   1. Close this window
    echo   2. Reinstall Vulkan SDK with "Add to PATH" checked
    echo   3. Open a NEW command window and run this script again
    echo.
    echo OR manually add to PATH:
    if defined VULKAN_SDK (
        echo   Add this to PATH: %VULKAN_SDK%\Bin
    ) else (
        echo   Add this to PATH: C:\VulkanSDK\1.3.xxx.x\Bin
    )
    set /a ERRORS+=1
)
echo.

REM ============================================================================
REM Check 3: Vulkan library (vulkan-1.lib)
REM ============================================================================
echo [3/5] Checking Vulkan library...

if defined VULKAN_SDK (
    if exist "%VULKAN_SDK%\Lib\vulkan-1.lib" (
        echo [OK] vulkan-1.lib found
        echo      Path: %VULKAN_SDK%\Lib\vulkan-1.lib
    ) else (
        echo [ERROR] vulkan-1.lib not found!
        echo.
        echo SOLUTION:
        echo   Reinstall Vulkan SDK and check ALL components
        set /a ERRORS+=1
    )
) else (
    echo [SKIP] Cannot check (VULKAN_SDK not set)
)
echo.

REM ============================================================================
REM Check 4: Vulkan headers
REM ============================================================================
echo [4/5] Checking Vulkan headers...

if defined VULKAN_SDK (
    if exist "%VULKAN_SDK%\Include\vulkan\vulkan.h" (
        echo [OK] vulkan.h found
        echo      Path: %VULKAN_SDK%\Include\vulkan\vulkan.h
    ) else (
        echo [ERROR] vulkan.h not found!
        echo.
        echo SOLUTION:
        echo   Reinstall Vulkan SDK and check ALL components
        set /a ERRORS+=1
    )
) else (
    echo [SKIP] Cannot check (VULKAN_SDK not set)
)
echo.

REM ============================================================================
REM Check 5: Validation layers
REM ============================================================================
echo [5/5] Checking validation layers...

if defined VULKAN_SDK (
    if exist "%VULKAN_SDK%\Bin\VkLayer_khronos_validation.dll" (
        echo [OK] Validation layers found
        echo      Path: %VULKAN_SDK%\Bin\VkLayer_khronos_validation.dll
    ) else (
        echo [WARNING] Validation layers not found
        echo           (Optional, but recommended for debugging)
    )
) else (
    echo [SKIP] Cannot check (VULKAN_SDK not set)
)
echo.

REM ============================================================================
REM Summary
REM ============================================================================
echo ========================================
if %ERRORS% EQU 0 (
    echo SUCCESS! Vulkan SDK is properly installed!
    echo ========================================
    echo.
    echo You can now build the Vulkan project:
    echo.
    echo   1. Compile shaders:
    echo      tools\compile_shaders.bat
    echo.
    echo   2. Configure CMake:
    echo      mkdir build
    echo      cd build
    echo      cmake ..
    echo.
    echo   3. Build project:
    echo      cmake --build . --config Debug
    echo.
    echo   4. Run application:
    echo      Debug\VulkanSandbox.exe
    echo.
) else (
    echo FAILED! Found %ERRORS% error(s)
    echo ========================================
    echo.
    echo Please fix the errors above and run this script again.
    echo.
    echo For detailed installation instructions, see:
    echo   install_vulkan_sdk.md
    echo.
    echo Common solutions:
    echo   1. Close this window and open a NEW command prompt
    echo   2. Reinstall Vulkan SDK with "Add to PATH" checked
    echo   3. Restart your computer
    echo.
)
echo ========================================
echo.

pause
