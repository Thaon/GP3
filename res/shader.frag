#version 330

uniform sampler2D texture_diffuse1;

in vec2 tex;
in vec4 col;
in vec3 cameraPos;
in vec3 vertexPos;

out vec4 fragCol;

void main()
{
	float dis = (6 - distance(vertexPos, cameraPos)) / 3;
	fragCol = vec4(dis, dis, dis, 1);
}
