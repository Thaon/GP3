#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 MVP;
uniform vec3 camPos;
uniform mat4 viewProj;

out vec3 v_pos;
out vec3 v_norm;
out vec3 cam;
out mat4 trans;
out mat4 view;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	view = viewProj;
	v_pos = position;
	v_norm = normal;
	cam = camPos;
	texCoord0 = texCoord;
}