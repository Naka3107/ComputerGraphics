#version 330

out vec4 FragColor;

in vec4 ColorOut;

void main()
{
	FragColor = ColorOut;
}