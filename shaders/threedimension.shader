#shader vertex
#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_inverse;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(vertex.xyz, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_cubeColor;

void main()
{
    color = vec4(u_cubeColor, 1.0);
}
