#version 330

out vec4 FragColor;

in vec4 ColorOut;
in vec3 VertexPositionOut;

void main()
{
	float magnitude = sqrt(VertexPositionOut.x*VertexPositionOut.x + VertexPositionOut.y*VertexPositionOut.y + VertexPositionOut.z*VertexPositionOut.z);
	if(magnitude <= 0.5){
		discard;
	}
	
	FragColor = ColorOut;
}