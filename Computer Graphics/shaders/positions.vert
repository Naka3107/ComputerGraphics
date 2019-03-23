#version 330

in vec3 VertexPositionIn;
in vec4 ColorIn;

out vec3 VertexPositionOut;
out vec4 ColorOut;

void main()
{
	gl_Position = vec4(VertexPositionIn, 1.0f);

	ColorOut = ColorIn;
	VertexPositionOut = VertexPositionIn;
}