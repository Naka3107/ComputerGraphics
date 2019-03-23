#version 330

uniform float time;

out vec4 InterpolatedColor;

vec2 circle()
{
  float PI = 3.14159f;
  float x = floor(gl_VertexID / 2.0f);
  float y = mod(gl_VertexID + 1.0f, 2.0f);
  
  float angle = x / 30.0f * 2 * PI;
  float radius = 2.0f - y;
  
  float u = radius * cos(angle);
  float v = radius * sin(angle);
  
  return vec2(u, v);
}


void main()
{
  float width = 10.0f;
  
  float circleId = floor(gl_VertexID/62.0f);
    
  float x = mod(circleId, width);
  float y = floor(circleId / width);
  
  float u = x / (width - 1.0f);
  float v = y / (width - 1.0f);
  
  float xOffset = cos(time + y * 0.2f) * 0.1f;
  float yOffset = cos(time + x * 0.3f) * 0.2f;
  
  float ux = u * 2.0f - 1.0f + xOffset;
  float vy = v * 2.0f - 1.0f + yOffset;
  
  vec2 xy = vec2(ux, vy)*1.2f;
  
  gl_Position = vec4(circle()*.05f+xy, 0.0f, 1.0f);
  InterpolatedColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}