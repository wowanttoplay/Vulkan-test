#version 450

// ============================================================================
// SIMPLE VERTEX SHADER - Phase 1
// ============================================================================
//
// 功能：
// - 接收顶点数据（位置、颜色）
// - 应用MVP变换
// - 传递颜色到片段着色器
//
// Later：添加光照计算、法线变换等

// 输入（来自Vertex结构体）
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

// Push Constants（MVP矩阵）
layout(push_constant) uniform PushConstants {
    mat4 mvp;
} push;

// 输出到片段着色器
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;

void main() {
    // 变换顶点位置
    gl_Position = push.mvp * vec4(inPosition, 1.0);

    // 传递属性到片段着色器
    fragColor = inColor;
    fragNormal = inNormal;  // Phase 1不使用，Later用于光照
    fragTexCoord = inTexCoord;  // Phase 1不使用，Later用于纹理
}
