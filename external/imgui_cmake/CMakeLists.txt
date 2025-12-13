cmake_minimum_required(VERSION 3.15)
project(imgui)

# ImGui源文件
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    # Backends
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

set(IMGUI_HEADERS
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imconfig.h
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h
    ${IMGUI_DIR}/imstb_truetype.h

    # Backends
    ${IMGUI_DIR}/backends/imgui_impl_glfw.h
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.h
)

# 创建静态库
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

# Include目录
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# 链接GLFW和Vulkan
target_link_libraries(imgui PUBLIC
    glfw
    Vulkan::Vulkan
)

# C++17
target_compile_features(imgui PUBLIC cxx_std_17)
