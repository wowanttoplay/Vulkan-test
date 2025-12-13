#version 450

// ============================================================================
// SIMPLE FRAGMENT SHADER - Phase 1
// ============================================================================
//
// 功能：
// - 接收顶点颜色
// - 直接输出颜色（无光照）
//
// Later：添加光照计算、纹理采样等

// 输入（来自顶点着色器）
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

// 输出
layout(location = 0) out vec4 outColor;

void main() {
    // Phase 1：直接输出顶点颜色
    outColor = vec4(fragColor, 1.0);

    // Later：添加光照
    // vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    // float diffuse = max(dot(normalize(fragNormal), lightDir), 0.0);
    // outColor = vec4(fragColor * diffuse, 1.0);

    // Later：添加纹理
    // vec4 texColor = texture(texSampler, fragTexCoord);
    // outColor = vec4(fragColor * texColor.rgb, 1.0);
}
