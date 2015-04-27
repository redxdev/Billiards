#version 430

in vec2 uv;
uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	outColor = texture2D(textureSampler, uv).rgba;
}