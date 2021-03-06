#version 330

in vec2 textureCoords;
in vec3 normal;
in vec3 position;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// ambiental
	vec3 ambiental = lightColor*0.1;

	// diffuse 
	vec3 lightVector = normalize(lightPosition - (modelMatrix*vec4(position, 1.0f)).xyz);
	vec3 normalVector = normalize(normalMatrix * normal);
	vec3 diffuse = lightColor * clamp(dot(lightVector, normalVector), 0.0, 1.0);

	// specular
	vec3 reflectVector = reflect(-lightVector, normalVector);
	vec3 viewVector = normalize(cameraPosition - position);
	vec3 specular =  lightColor * pow(clamp(dot(lightVector, normalVector), 0.0, 1.0), 16.0);

	// texture color
	vec3 texture_color = mix(
		texture2D(texture1, textureCoords),
		texture2D(texture2, textureCoords),
		0.5
	).xyz;

	vec3 phong = (ambiental + diffuse + specular) * texture_color; 
	
	FragColor = vec4(phong, 1.0);
	

	// phong
//	vec3 phong = (specular) * texture_color; 
}