#version 330

in vec3 VertexPosition;
in vec2 TexturePosition;

out vec2 TextureColor;


uniform mat4 mvpMatrix;

void main() {
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);

	TextureColor = TexturePosition;
}
