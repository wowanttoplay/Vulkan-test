@echo off
REM ============================================================================
REM Vulkan SDK Download Helper
REM ============================================================================

echo ========================================
echo Vulkan SDK Download Helper
echo ========================================
echo.
echo This script will help you download and install Vulkan SDK.
echo.
echo Opening Vulkan SDK download page in your browser...
echo.

REM Open the Vulkan SDK download page
start https://vulkan.lunarg.com/sdk/home#windows

echo ========================================
echo Download Instructions:
echo ========================================
echo.
echo 1. In the browser window that just opened:
echo    - Click the "Download Latest SDK" button
echo    - OR scroll to "Windows" section and click download
echo.
echo 2. Wait for download to complete
echo    File name: VulkanSDK-1.3.xxx.x-Installer.exe
echo    Size: About 200-400 MB
echo.
echo 3. Run the downloaded installer:
echo    - Double-click the .exe file
echo    - Accept the license agreement
echo    - CHECK ALL COMPONENTS (especially Shader Toolchain)
echo    - IMPORTANT: Check "Add to PATH" option
echo    - Click Install
echo    - Wait for installation to complete
echo.
echo 4. After installation:
echo    - Close this command window
echo    - Open a NEW command window
echo    - Run: verify_vulkan_installation.bat
echo.
echo ========================================
echo.
echo Press any key after you've started the download...
pause > nul

echo.
echo ========================================
echo Installation Tips:
echo ========================================
echo.
echo [!] IMPORTANT CHECKBOXES during installation:
echo     [x] Vulkan SDK Core
echo     [x] Shader Toolchain (includes glslc)
echo     [x] Debugging Tools
echo     [x] Add to PATH
echo.
echo [!] Default installation path is RECOMMENDED:
echo     C:\VulkanSDK\1.3.xxx.x
echo.
echo [!] After installation completes:
echo     1. CLOSE this command window
echo     2. Open a NEW command window
echo     3. Run: verify_vulkan_installation.bat
echo.
echo ========================================
echo.

REM Wait for user to finish installation
echo Waiting for you to complete the installation...
echo.
echo Press any key AFTER installation is complete...
pause > nul

echo.
echo ========================================
echo Checking if Vulkan SDK was installed...
echo ========================================
echo.

REM Check if VULKAN_SDK is set (might not be visible in current session)
if defined VULKAN_SDK (
    echo [OK] VULKAN_SDK environment variable detected!
    echo      Path: %VULKAN_SDK%
    echo.
    echo [!] If the path above is correct, Vulkan SDK is installed!
    echo     Run verify_vulkan_installation.bat in a NEW window to confirm.
) else (
    echo [!] VULKAN_SDK environment variable not detected in current session.
    echo.
    echo This is NORMAL! Environment variables require a new command window.
    echo.
    echo Next steps:
    echo   1. CLOSE this window
    echo   2. Open a NEW command prompt
    echo   3. Run: verify_vulkan_installation.bat
)

echo.
echo ========================================
echo.
pause
