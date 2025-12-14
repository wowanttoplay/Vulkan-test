# Vulkan Learning Sandbox

A project framework for learning Vulkan API and experimenting with rendering techniques.

## Project Philosophy

**You learn Vulkan, I build the framework**
- Framework code (ECS, UI, scene management) is complete
- Vulkan code provides learning templates with TODOs
- Step-by-step guidance for learning Vulkan core concepts

## Quick Start

### Prerequisites

1. **Vulkan SDK** (1.3+) - [Download](https://vulkan.lunarg.com/sdk/home)
2. **CMake** (3.20+) - [Download](https://cmake.org/download/)
3. **Visual Studio 2022** with C++17 support

### Build & Run

```batch
# Build the project
build_project.bat

# Run the application
run_project.bat
```

The program will stop at the first TODO with a clear error message telling you what to implement.

## Project Structure

```
Vulkan-test/
├── src/
│   ├── Core/           # Vulkan abstractions (YOUR LEARNING FOCUS)
│   ├── ECS/            # Entity-Component-System (complete)
│   ├── Framework/      # Application framework (complete)
│   └── Rendering/      # Rendering system
├── shaders/            # GLSL shaders
├── external/           # Third-party libraries
├── scripts/            # Setup and utility scripts
├── build_project.bat   # Build script
└── run_project.bat     # Run script
```

## Scripts

| Script | Description |
|--------|-------------|
| `build_project.bat` | Compile shaders + CMake configure + Build |
| `run_project.bat` | Run the application |
| `scripts/compile_shaders.bat` | Compile GLSL shaders to SPIR-V |
| `scripts/verify_vulkan_installation.bat` | Verify Vulkan SDK installation |
| `scripts/install_cmake.bat` | Download and install CMake |
| `scripts/download_vulkan_sdk.bat` | Open Vulkan SDK download page |

## Learning Path

### Phase 1: Render a Cube
Implement TODOs in order:

1. **VulkanContext.cpp** - Instance, Device, Queues
2. **VulkanSwapchain.cpp** - Swapchain, Image Views
3. **VulkanPipeline.cpp** - Graphics Pipeline
4. **VulkanBuffer.cpp** - Vertex/Index Buffers
5. **Renderer.cpp** - Render Loop

Each TODO includes:
- Concept explanation
- Implementation hints
- Reference links to vulkan-tutorial.com

### Future Phases
- Phase 2: Object Picking (Ray Casting)
- Phase 3: Scene Editing (ImGui)
- Phase 4: PBR Materials
- Phase 5+: Advanced Effects (Shadows, Sky, Water)

## Manual Build

If you prefer manual commands:

```batch
# 1. Compile shaders
scripts\compile_shaders.bat

# 2. Configure CMake
mkdir build
cd build
cmake ..

# 3. Build
cmake --build . --config Debug

# 4. Run
bin\Debug\VulkanSandbox.exe
```

## Troubleshooting

### "glslc not found"
- Verify Vulkan SDK is installed: `scripts\verify_vulkan_installation.bat`
- Restart your terminal after installing Vulkan SDK

### "CMake not found"
- Install CMake and add to PATH
- Or use: `scripts\install_cmake.bat`

### Build fails
- Ensure Visual Studio 2022 with C++ workload is installed
- Check that Vulkan SDK environment variables are set

## Resources

- [Vulkan Tutorial](https://vulkan-tutorial.com/) - Main learning resource
- `docs/PHASE1_GUIDE.md` - Detailed Phase 1 guide
- `CLAUDE.md` - Project architecture notes
