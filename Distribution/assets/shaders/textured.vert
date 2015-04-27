#version 430

in vec2 position;
in vec2 vertexUV;

out vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	uv = vertexUV;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 0, 1);
}
