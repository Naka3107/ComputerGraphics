#version 330

in vec2 TextureColor;
uniform sampler2D texture;

out vec4 FragColor;

void main() { 
	vec4 TextureShadow = texture2D(texture, TextureColor); 
	if (TextureShadow.w < 0.55)
		discard;
			
	FragColor = vec4(gl_FragCoord.z, 
					gl_FragCoord.z, 
					gl_FragCoord.z,
					1.0f);
}