#shader vertex
#version 330 core

layout (location = 0) in vec2 vertex;

uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_model * vec4(vertex.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_spriteColor;

void main()
{
    color = u_spriteColor;
}