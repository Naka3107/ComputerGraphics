#version 330


in vec2 texturePosition;

in vec3 VertexPosition;
uniform mat4 mvpMatrix;

out vec2 textureCoords;

void main()
{
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0);
	textureCoords = texturePosition;
}