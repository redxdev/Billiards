#version 430

in vec4
uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	outColor = texture2D(textureSampler, gl_TexCoord[0].xy);
}