#version 330

in vec3 VertexPosition;
in vec2 TexturePosition;
in vec3 NormalPosition;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec2 textureCoords;
out vec3 normal;
out vec3 position;
out vec4 pixelPosition;

void main()
{
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0);
	textureCoords = TexturePosition;
	position = vec3(modelMatrix * vec4(VertexPosition, 1.0));
	normal = NormalPosition;
}