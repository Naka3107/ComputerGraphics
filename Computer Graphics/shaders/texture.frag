#version 330

in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture2D(texture1, textureCoords), texture2D(texture2, textureCoords), 0.25f);
}