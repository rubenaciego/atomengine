R"(#version 400 core

layout(location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 texCoord;
	float texID;
	vec4 color;
} fs_in;

uniform sampler2D u_Textures[16];

void main()
{
	color = fs_in.color;

	if (fs_in.texID > 0.0)
		color *= texture(u_Textures[int(fs_in.texID - 0.5)], fs_in.texCoord);
}
)"
