#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;

uniform mat4 MVP;
uniform mat4 camPos;

out vec4 v_pos;
out vec3 v_norm;
out mat4 cam;

void main()
{
	cam = camPos;
	gl_Position = MVP * vec4(position, 1.0);
	v_pos = vec4(position, 1.0);
	v_norm = normal;
	texCoord0 = texCoord;
}