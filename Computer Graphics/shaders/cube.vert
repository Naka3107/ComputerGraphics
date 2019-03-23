#version 330

in vec3 VertexPosition;
in vec4 ColorIn;

uniform mat4 mvpMatrix;

out vec4 ColorOut;

void main()
{
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0);
	ColorOut = ColorIn;
}