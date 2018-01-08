#version 330

layout( location = 0 ) out vec4 fragcolor;
 
in vec3 v_norm;
in vec3 v_pos;
in vec3 cam;
in mat4 trans;
in mat4 view;

varying vec2 texCoord0;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
 
void main()
{
  vec3 n = normalize(cam * v_norm);
  vec3 p = vec3(cam * v_pos);
  vec3 v = normalize(-p);

  
  float vdn = 1.0 - max(dot(v, n), 0.0);

  fragcolor.a = 1.0;
  fragcolor.rgb = vec3(smoothstep(0.6, 1.0, vdn));
}