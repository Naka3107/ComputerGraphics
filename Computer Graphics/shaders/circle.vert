void main()
{
  float x = floor(vertexId / 2.0);
  float y = mod(vertexId + 1.0, 2.0);
  
  float angle = x / 20.0 * radians(360.0);
  float radius = 2.0 - y;
  
  float u = radius * cos(angle);
  float v = radius * sin(angle);
  
  vec2 xy = vec2(u, v) * 0.1;
  

  gl_Position = vec4(xy, 0.0, 1.0);
  gl_PointSize = 20.0;
  v_color = vec4(0.0, 0.0, 0.0, 1.0);
}