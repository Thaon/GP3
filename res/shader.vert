#version 330

uniform mat4 MVP;
uniform vec3 camPos;

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec3 vertColor;

out vec2 tex;
out vec4 col;
out vec3 cameraPos;
out vec3 vertexPos;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	tex = texCoord;
	col = gl_Position;
	cameraPos = camPos;
	vertexPos = position;
}