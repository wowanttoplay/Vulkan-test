@echo off
REM ============================================================================
REM Shader编译脚本
REM ============================================================================
REM
REM 功能：
REM - 将GLSL着色器编译成SPIR-V
REM - 自动创建输出目录
REM - 编译所有.vert和.frag文件
REM
REM 使用方法：
REM   双击运行或在命令行执行：tools\compile_shaders.bat
REM
REM 要求：
REM - Vulkan SDK已安装
REM - glslc在PATH中（通常随Vulkan SDK安装）

echo ========================================
echo Compiling shaders...
echo ========================================

REM 创建输出目录
if not exist shaders\compiled mkdir shaders\compiled

REM 编译顶点着色器
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

REM 编译片段着色器
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

REM 保持窗口打开
pause
