#version 330

uniform float time;

out vec4 InterpolatedColor;

void main()
{
  float angle1 = radians(floor(gl_VertexID / 180.0f))*2.0f;
  float angle2 = radians(mod(gl_VertexID, 360.0f))*2.0f;
 
  float radius = 10.0;
  
  float u = radius * sin(angle1) * cos(angle2);
  float v = radius * sin(angle1) * sin(angle2);
  float w = radius * cos(angle1);
  
  float rotationAngle = time;
  
  mat3 rotationX = mat3(1,0,0,0,cos(rotationAngle),-sin(rotationAngle),0,sin(rotationAngle),cos(rotationAngle));
  mat3 rotationY = mat3(cos(rotationAngle),0,sin(rotationAngle),0,1,0,-sin(rotationAngle),0,cos(rotationAngle));
  
  vec3 xyz = vec3(u, v, w) * 0.1f * rotationX * rotationY;
  
  gl_Position = vec4(xyz, 1.0f);
  gl_PointSize = 2.0f;
  InterpolatedColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
