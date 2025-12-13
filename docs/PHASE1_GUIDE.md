# Phase 1 学习指南：Vulkan基础

## 欢迎！

恭喜你开始Vulkan学习之旅！这个指南将引导你完成Phase 1，在这个阶段你将学会Vulkan的核心概念并渲染你的第一个立方体。

## 学习目标

完成Phase 1后，你将掌握：
- ✅ Vulkan初始化流程
- ✅ 交换链创建和管理
- ✅ 图形管线构建
- ✅ 缓冲区和内存管理
- ✅ 命令缓冲区录制
- ✅ 同步机制（信号量、栅栏）

## 框架已为你准备好

**你不需要担心的部分（已完成）**：
- ✅ ECS系统 - 场景对象管理
- ✅ 窗口系统 - GLFW集成
- ✅ 相机控制 - WASD + 鼠标
- ✅ ImGui集成 - 调试UI
- ✅ 输入处理 - 键盘鼠标事件

**你的学习重点（需要实现）**：
- 📝 Vulkan初始化
- 📝 交换链
- 📝 图形管线
- 📝 缓冲区
- 📝 渲染循环

## 学习流程

### Step 1: Vulkan Instance 和 Device (2-3小时)

**文件**: `src/Core/VulkanContext.h/cpp`

**要实现的TODO**:
1. `createInstance()` - 创建Vulkan实例
2. `setupDebugMessenger()` - 设置验证层
3. `createSurface()` - 创建窗口表面
4. `pickPhysicalDevice()` - 选择GPU
5. `createLogicalDevice()` - 创建逻辑设备

**学习资源**:
- [Vulkan Tutorial - Instance](https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance)
- [Vulkan Tutorial - Validation Layers](https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Validation_layers)
- [Vulkan Tutorial - Physical Devices](https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families)

**验证方法**:
```cpp
// 在完成后，运行程序应该看到：
// - Vulkan instance created successfully
// - Validation layers enabled
// - Physical device: NVIDIA GeForce RTX... (或你的GPU)
// - Logical device created
```

---

### Step 2: Swapchain (1-2小时)

**文件**: `src/Core/VulkanSwapchain.h/cpp`

**要实现的TODO**:
1. `createSwapchain()` - 创建交换链
2. `createImageViews()` - 创建图像视图
3. `recreateSwapchain()` - 窗口resize时重建

**关键概念**:
- **Surface Format**: 图像格式（BGRA8, SRGB等）
- **Present Mode**: 呈现模式（Immediate, FIFO, Mailbox）
- **Extent**: 交换链图像尺寸

**学习资源**:
- [Vulkan Tutorial - Swap Chain](https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain)
- [Vulkan Tutorial - Image Views](https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Image_views)

---

### Step 3: Graphics Pipeline (2-3小时)

**文件**: `src/Core/VulkanPipeline.h/cpp`

**要实现的TODO**:
1. `createShaderModule()` - 加载着色器
2. `createGraphicsPipeline()` - 创建图形管线
3. `createRenderPass()` - 创建渲染通道
4. `createFramebuffers()` - 创建帧缓冲

**关键概念**:
- **Shader Stages**: Vertex, Fragment
- **Vertex Input**: 顶点属性描述
- **Input Assembly**: 图元拓扑（Triangle List）
- **Viewport/Scissor**: 视口和裁剪
- **Rasterization**: 光栅化设置
- **Color Blending**: 混合设置

**学习资源**:
- [Vulkan Tutorial - Graphics Pipeline](https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics)
- [Vulkan Tutorial - Render Passes](https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Render_passes)

---

### Step 4: Buffers (1-2小时)

**文件**: `src/Core/VulkanBuffer.h/cpp`

**要实现的TODO**:
1. `createBuffer()` - 创建缓冲区
2. `allocateMemory()` - 分配内存
3. `copyBuffer()` - 复制缓冲区（使用staging buffer）

**关键概念**:
- **Vertex Buffer**: 顶点数据
- **Index Buffer**: 索引数据
- **Staging Buffer**: 临时缓冲区（CPU可见）
- **Device Local**: GPU本地内存（最快）

**学习资源**:
- [Vulkan Tutorial - Vertex Buffers](https://vulkan-tutorial.com/Vertex_buffers/Vertex_buffer_creation)
- [Vulkan Tutorial - Index Buffers](https://vulkan-tutorial.com/Vertex_buffers/Index_buffer)

---

### Step 5: Rendering Loop (2-3小时)

**文件**: `src/Rendering/Renderer.cpp`, `src/Rendering/ForwardPass.cpp`

**要实现的TODO**:
1. `createCommandPool()` - 创建命令池
2. `createCommandBuffers()` - 创建命令缓冲区
3. `recordCommandBuffer()` - 录制命令
4. `createSyncObjects()` - 创建同步对象
5. `drawFrame()` - 主渲染循环

**关键概念**:
- **Command Pool**: 命令缓冲区内存池
- **Command Buffer**: 记录GPU命令
- **Semaphore**: GPU-GPU同步
- **Fence**: GPU-CPU同步
- **Frames in Flight**: 多帧并行

**学习资源**:
- [Vulkan Tutorial - Command Buffers](https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Command_buffers)
- [Vulkan Tutorial - Rendering](https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Rendering_and_presentation)

---

## 实现顺序

**建议按以下顺序实现**:
1. VulkanContext (所有5个TODO)
2. VulkanSwapchain (所有3个TODO)
3. VulkanPipeline (所有4个TODO)
4. VulkanBuffer (所有3个TODO)
5. Renderer + ForwardPass (所有5个TODO)

每完成一个文件，编译并运行，确保没有错误。

## 调试技巧

### 1. 使用验证层
```cpp
// 验证层会捕获大部分错误
// 仔细阅读验证层输出！
```

### 2. 检查返回值
```cpp
VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
if (result != VK_SUCCESS) {
    // 打印错误码
    std::cerr << "Failed to create instance! Error: " << result << std::endl;
}
```

### 3. 使用RenderDoc
RenderDoc可以捕获Vulkan帧并查看所有状态。

### 4. 参考实现
如果卡住了，查看 `docs/REFERENCE_IMPL.md` 中的参考实现。

## 常见问题

### Q: Validation layer错误太多怎么办？
A: 一个一个修复！最上面的错误通常是根本原因，修复它后很多错误会消失。

### Q: 编译错误找不到Vulkan头文件？
A: 确保安装了Vulkan SDK，并设置了VULKAN_SDK环境变量。

### Q: 程序运行但黑屏？
A: 检查：
- 交换链是否创建成功？
- 命令缓冲区是否正确录制？
- 同步对象是否正确？
- 着色器是否编译？

### Q: 窗口resize时崩溃？
A: 需要实现 `VulkanSwapchain::recreateSwapchain()`。

## 完成标志

当你看到一个旋转的彩色立方体时，恭喜你完成了Phase 1！

## 下一步

完成Phase 1后，你将：
- Phase 2: 实现对象拾取（学习射线投射）
- Phase 3: 场景编辑UI
- Phase 4: PBR材质
- Phase 5+: 阴影、天空、水、后处理等

每个阶段都会教你新的Vulkan概念！

## 需要帮助？

1. 查看 `docs/REFERENCE_IMPL.md` - 参考实现
2. 查看 Vulkan Tutorial - 详细教程
3. 查看 Vulkan规范 - 官方文档

祝学习愉快！🚀
