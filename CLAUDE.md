# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Vulkan graphics application project. The repository is currently empty and awaiting initial setup.

## Development Setup

When setting up this project, typical Vulkan projects require:

1. **Vulkan SDK**: Ensure the Vulkan SDK is installed and environment variables are set
   - `VULKAN_SDK` should point to the SDK installation directory
   - Common path on Windows: `C:\VulkanSDK\<version>`

2. **Build System**: Common options for Vulkan projects:
   - Visual Studio solution (.sln) for Windows development
   - CMake for cross-platform builds
   - Makefile for Unix-like systems

3. **Dependencies**: Vulkan projects typically depend on:
   - GLFW or SDL2 for window management
   - GLM for mathematics
   - shaderc or glslc for shader compilation
   - Vulkan validation layers for debugging

## Build Commands

Once the project is set up, typical commands will include:

**Windows (Visual Studio)**:
- Build: `msbuild Vulkan-test.sln /p:Configuration=Debug`
- Build Release: `msbuild Vulkan-test.sln /p:Configuration=Release`

**CMake**:
- Configure: `cmake -B build`
- Build: `cmake --build build`
- Build specific target: `cmake --build build --target <target_name>`

## Code Architecture

Typical Vulkan application architecture includes:

1. **Initialization Pipeline**:
   - Instance creation → Physical device selection → Logical device creation
   - Surface creation → Swapchain setup
   - Graphics pipeline setup (shaders, render passes, framebuffers)

2. **Render Loop**:
   - Acquire swapchain image
   - Record command buffers
   - Submit to queue
   - Present to screen

3. **Resource Management**:
   - Proper cleanup in reverse order of creation
   - Synchronization primitives (semaphores, fences)
   - Memory allocation and buffer management

4. **Validation Layers**:
   - Enable in debug builds for error checking
   - Disable in release builds for performance

## Shader Development

- Shaders are typically written in GLSL and compiled to SPIR-V
- Common shader files: `.vert`, `.frag`, `.comp`, `.geom`, `.tesc`, `.tese`
- Compilation: `glslc shader.vert -o vert.spv` or use build system integration

## Important Notes

- Vulkan requires explicit synchronization - always verify proper use of semaphores and fences
- Validation layers are critical during development - check console output for errors
- Memory management is manual - ensure proper allocation and deallocation
- Swapchain recreation is needed when window resizes or other surface changes occur
