#version 330

in vec2 textureCoords;
in vec3 normal;
in vec3 position;
in vec4 pixelPosition;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform mat3 normalMatrix;

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

float occlusion()
{
	vec3 projCoords = pixelPosition.xyz / pixelPosition.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture2D(depthTexture, projCoords.xy).r;
	float currentDepth = projCoords.z;

	return currentDepth - 0.005 > closestDepth ? 1.0 : 0.0;
}

void main()
{
	// ambiental
	vec3 ambiental = lightColor*0.1;

	// diffuse 
	vec3 lightVector = normalize(lightPosition - position);
	vec3 normalVector = normalize(normalMatrix * normal);
	vec3 diffuse = lightColor * clamp(dot(lightVector, normalVector), 0.0, 1.0);

	// specular
	vec3 reflectVector = reflect(-lightVector, normalVector);
	vec3 viewVector = normalize(cameraPosition - position);
	vec3 specular =  lightColor * pow(clamp(dot(reflectVector, normalVector), 0.0, 1.0), 16.0);

	// texture color
	vec4 texture_color = texture2D(colorTexture, textureCoords);


	vec4 phong = vec4((ambiental + (1.0 - occlusion()) * (diffuse + specular)), 1.0) * texture_color; 
	
	FragColor = phong;
}