#version 330

uniform vec2 iResolution;
uniform float iTime;

out vec4 FragColor;

void main()
{
    vec2 p = gl_FragCoord.xy / iResolution.xy;
    vec2 q = p - vec2(0.35f, 0.7f);
    
    vec3 color = mix(vec3(1.0f, 0.4f, 0.1f), vec3(1.0f, 0.8f, 0.3f), sqrt(p.y));
    
    float r = 0.2f + 0.1f * cos(atan(q.y, q.x) * 10.0f + 20.0f * (0.75f + 0.25f * cos(iTime)) * q.x + 1.0f);
    color *= smoothstep(r, r + 0.01f, length(q));
    
    r = 0.015f;
    r += 0.002f * cos(120.0f * q.y);
    r += exp(-40.0f * p.y);
    color *= 1.0f - (1.0f - smoothstep(r, r + 0.002f, abs(q.x - 0.25f * sin(2.0f * q.y)))) * (1.0f - smoothstep(0.0f, 0.01f, q.y));
                    
    FragColor = vec4(color, 1.0f);
}