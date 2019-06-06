#shader vertex
#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 v_TexCoord;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(vertex.xy, 0.0f, 1.0f);
    v_TexCoord = vertex.zw;
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform vec3 u_textColor;
uniform sampler2D u_text;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_text, v_TexCoord).r);
    color = vec4(u_textColor, 1.0) * sampled;
}
