#version 330

in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
	FragColor = texture2D(texture1, textureCoords);
}