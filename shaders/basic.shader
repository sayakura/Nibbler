#shader vertex
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_model * vec4(vertex.xy, 0.0f, 1.0f);
    v_TexCoord = texCoord.xy;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec3 u_spriteColor;
uniform sampler2D u_Image;

void main()
{
    color = vec4(u_spriteColor, 1.0) * texture(u_Image, v_TexCoord);
}
