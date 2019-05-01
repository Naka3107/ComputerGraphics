#version 330

in vec3 VertexPosition;
in vec2 texturePosition;

uniform mat4 mvpMatrix;

out vec2 textureCoords;

void main()
{
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0);
	textureCoords = texturePosition;
}