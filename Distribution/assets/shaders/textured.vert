#version 430

in vec2 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 0, 1);
}
