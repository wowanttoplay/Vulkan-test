@echo off
REM ============================================================================
REM Shader Compilation Script
REM ============================================================================
REM
REM Features:
REM - Compiles GLSL shaders to SPIR-V
REM - Auto-creates output directory
REM - Compiles all .vert and .frag files
REM
REM Usage:
REM   Double-click or run: tools\compile_shaders.bat
REM
REM Requirements:
REM - Vulkan SDK installed
REM - glslc in PATH (comes with Vulkan SDK)

echo ========================================
echo Compiling shaders...
echo ========================================

REM Create output directory
if not exist shaders\compiled mkdir shaders\compiled

REM Compile vertex shaders
echo Compiling vertex shaders...
for %%f in (shaders\*.vert) do (
    echo   %%f -^> shaders\compiled\%%~nf.vert.spv
    glslc %%f -o shaders\compiled\%%~nf.vert.spv
    if errorlevel 1 (
        echo ERROR: Failed to compile %%f
        pause
        exit /b 1
    )
)

REM Compile fragment shaders
echo Compiling fragment shaders...
for %%f in (shaders\*.frag) do (
    echo   %%f -^> shaders\compiled\%%~nf.frag.spv
    glslc %%f -o shaders\compiled\%%~nf.frag.spv
    if errorlevel 1 (
        echo ERROR: Failed to compile %%f
        pause
        exit /b 1
    )
)

echo.
echo ========================================
echo All shaders compiled successfully!
echo ========================================
echo.

REM Keep window open
pause
