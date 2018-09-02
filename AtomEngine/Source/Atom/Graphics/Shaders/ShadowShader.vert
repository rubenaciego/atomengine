R"(#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texID;
layout(location = 3) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec2 texCoord;
	float texID;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * position;
	
	vs_out.position = position;
	vs_out.texCoord = texCoord;
	vs_out.texID = texID;
	vs_out.color = color;
}
)"
