@echo off
REM ============================================================================
REM Automated Build Script for Vulkan Learning Project
REM ============================================================================

echo ========================================
echo Vulkan Project Build Script
echo ========================================
echo.

REM Verify glslc is available (using system PATH)
where glslc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] glslc not found!
    echo         Make sure Vulkan SDK is installed.
    pause
    exit /b 1
)

echo [OK] glslc found
glslc --version
echo.

REM ============================================================================
REM Step 1: Compile Shaders
REM ============================================================================
echo ========================================
echo [1/4] Compiling shaders...
echo ========================================
echo.

if not exist shaders\compiled mkdir shaders\compiled

echo Compiling vertex shaders...
for %%f in (shaders\*.vert) do (
    echo   %%f -^> shaders\compiled\%%~nf.vert.spv
    glslc %%f -o shaders\compiled\%%~nf.vert.spv
    if errorlevel 1 (
        echo [ERROR] Failed to compile %%f
        pause
        exit /b 1
    )
)

echo Compiling fragment shaders...
for %%f in (shaders\*.frag) do (
    echo   %%f -^> shaders\compiled\%%~nf.frag.spv
    glslc %%f -o shaders\compiled\%%~nf.frag.spv
    if errorlevel 1 (
        echo [ERROR] Failed to compile %%f
        pause
        exit /b 1
    )
)

echo.
echo [OK] Shaders compiled successfully!
echo.

REM ============================================================================
REM Step 2: Create build directory
REM ============================================================================
echo ========================================
echo [2/4] Creating build directory...
echo ========================================
echo.

if not exist build mkdir build
cd build

echo [OK] Build directory ready
echo.

REM ============================================================================
REM Step 3: Configure with CMake
REM ============================================================================
echo ========================================
echo [3/4] Configuring with CMake...
echo ========================================
echo.

cmake ..
if errorlevel 1 (
    echo.
    echo [ERROR] CMake configuration failed!
    echo.
    echo Common issues:
    echo   - CMake not installed or not in PATH
    echo   - Vulkan SDK not found
    echo   - External dependencies missing
    echo.
    cd ..
    pause
    exit /b 1
)

echo.
echo [OK] CMake configuration successful!
echo.

REM ============================================================================
REM Step 4: Build the project
REM ============================================================================
echo ========================================
echo [4/4] Building the project...
echo ========================================
echo.
echo This may take 5-10 minutes on first build...
echo.

cmake --build . --config Debug
if errorlevel 1 (
    echo.
    echo [ERROR] Build failed!
    echo.
    echo Check the error messages above.
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo BUILD SUCCESS!
echo ========================================
echo.

cd ..

echo Project built successfully!
echo.
echo Executable: build\bin\Debug\VulkanSandbox.exe
echo.
echo To run: run_project.bat
echo.

pause
