#version 330

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;

out vec2 tex;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	tex = texCoord;
}