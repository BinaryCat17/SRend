#version 450

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inUV;
layout (location = 2) in vec4 inColor;

layout (location = 0) out vec2 outUV;
layout (location = 1) out vec4 outColor;

layout (binding = 1) uniform Ubo
{
    vec2 scale;
    vec2 translate;
};

void main()
{
    outUV = inUV;
    outColor = inColor;
    gl_Position = vec4(inPos * scale + translate, 0.0, 1.0);
}