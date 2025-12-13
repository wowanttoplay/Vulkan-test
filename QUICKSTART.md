# Vulkan Learning Project - Quick Start Guide

## Prerequisites

### 1. Install Vulkan SDK (REQUIRED)
Download and install from: https://vulkan.lunarg.com/

**Windows:**
- Download the installer for your platform
- Run the installer
- Verify installation: `echo %VULKAN_SDK%` should show the SDK path
- Verify glslc: `glslc --version` should work

### 2. Install Git (REQUIRED)
Download from: https://git-scm.com/downloads

### 3. Install CMake (REQUIRED)
Download from: https://cmake.org/download/
- Version 3.20 or higher required

### 4. Install Visual Studio (Windows)
Visual Studio 2019 or later with C++ development tools

## Setup Steps

### Step 1: Clone the Repository
If you haven't already:
```bash
git clone <your-repo-url>
cd Vulkan-test
```

### Step 2: Download External Dependencies
Run the setup script:
```bash
setup_dependencies.bat
```

This will download:
- **GLFW** (3.4) - Window management
- **GLM** (0.9.9.8) - Math library
- **VMA** (3.0.1) - Vulkan Memory Allocator
- **ImGui** (1.90.1) - UI library

**Note:** This will take a few minutes depending on your internet connection.

### Step 3: Compile Shaders
```bash
tools\compile_shaders.bat
```

This compiles GLSL shaders to SPIR-V format.

### Step 4: Configure with CMake
```bash
mkdir build
cd build
cmake ..
```

**Expected output:** CMake should find Vulkan SDK and configure successfully.

**Common issues:**
- **"Could not find Vulkan"**: Make sure VULKAN_SDK environment variable is set
- **"GLFW not found"**: Make sure you ran `setup_dependencies.bat`
- **"Git not found"**: Make sure Git is in your PATH

### Step 5: Build the Project
```bash
cmake --build . --config Debug
```

**First build will take a while** as it compiles GLFW and other dependencies.

### Step 6: Run the Application
```bash
Debug\VulkanSandbox.exe
```

**Expected behavior:**
- Program will start
- Window initialization messages
- **Program will stop at first TODO** with a clear error message:
  ```
  ========================================
  TODO NOT IMPLEMENTED:
    createInstance() in VulkanContext.cpp

  TASK:
    Implement Vulkan instance creation

  REFERENCE:
    - VulkanContext.h (TODO 1 comments)
    - https://vulkan-tutorial.com/...
  ========================================
  ```

**This is expected!** You now need to implement the TODOs.

## Next Steps

### Phase 1 Learning Path

Follow `docs/PHASE1_GUIDE.md` for detailed instructions.

**Summary:**
1. **VulkanContext** (src/Core/VulkanContext.cpp) - 5 TODOs
   - Create Vulkan instance
   - Setup debug messenger
   - Create surface
   - Pick physical device
   - Create logical device

2. **VulkanSwapchain** (src/Core/VulkanSwapchain.cpp) - 6 TODOs
   - Query swapchain support
   - Choose formats and modes
   - Create swapchain and image views

3. **VulkanPipeline** (src/Core/VulkanPipeline.cpp) - 3 TODOs
   - Load shaders
   - Create pipeline layout
   - Build graphics pipeline

4. **VulkanBuffer** (src/Core/VulkanBuffer.cpp) - 3 TODOs
   - Create buffers with VMA
   - Map memory
   - Copy buffer data

5. **Renderer** (src/Rendering/Renderer.cpp) - 7 TODOs
   - Create render pass
   - Create depth resources
   - Create framebuffers
   - Create command pools and buffers
   - Create sync objects
   - Record commands

### After All TODOs Complete

You'll see a **rotating colorful cube**! 🎉

Then you can:
- Experiment with different materials
- Add new geometric shapes
- Implement PBR rendering
- Add shadow mapping
- Try water/glass effects
- ... and more!

## Controls

**Camera:**
- `W/A/S/D` - Move camera
- `Right Mouse Button` - Capture mouse and look around
- `E` or `Space` - Move up
- `Q` or `Shift` - Move down
- `ESC` - Exit

## Troubleshooting

### CMake can't find Vulkan SDK
```bash
# Windows - Check environment variable
echo %VULKAN_SDK%

# Should output something like:
# C:\VulkanSDK\1.3.xxx.x
```

If not set, reinstall Vulkan SDK or set manually:
```bash
set VULKAN_SDK=C:\VulkanSDK\1.3.xxx.x
```

### "External dependencies not found"
Make sure you ran:
```bash
setup_dependencies.bat
```

Check that `external/` directory contains:
- `glfw/`
- `glm/`
- `vma/`
- `imgui/`
- `imgui_cmake/`

### Build errors about missing headers
Rebuild from scratch:
```bash
cd build
cmake --build . --config Debug --clean-first
```

### Runtime error: "Failed to load shader"
Make sure shaders are compiled:
```bash
tools\compile_shaders.bat
```

Check that `build/bin/shaders/` contains `.spv` files.

## Project Structure

```
Vulkan-test/
├── src/
│   ├── Core/           # Vulkan wrappers (YOUR WORK)
│   ├── ECS/            # Entity-Component-System (DONE)
│   ├── Framework/      # Window, Camera, Input (DONE)
│   └── Rendering/      # Renderer, Materials, Mesh (MIXED)
├── shaders/            # GLSL shaders
├── docs/               # Documentation
├── external/           # Downloaded dependencies
├── tools/              # Build scripts
└── build/              # CMake build directory
```

## Learning Resources

- **Vulkan Tutorial**: https://vulkan-tutorial.com/
- **VMA Documentation**: https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/
- **GLFW Documentation**: https://www.glfw.org/documentation.html
- **ImGui Wiki**: https://github.com/ocornut/imgui/wiki

## Getting Help

If you get stuck:
1. Check the TODO comments in the code
2. Read `docs/PHASE1_GUIDE.md`
3. Consult the Vulkan Tutorial links
4. Check validation layer messages (very helpful!)

Good luck with your Vulkan learning journey! 🚀
