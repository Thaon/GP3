#version 330

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec3 vertColor;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform vec3 camPos;
uniform vec3 lightDir;
uniform float lightIntensity;

out vec2 tex;
out vec4 col;
out vec3 cameraPos;
out vec3 vertexPos;

out float lightColor;

void main()
{
	tex = texCoord;
	vec3 norm = (modelMatrix * vec4(normal, 1.0)).xyz;

	vec3 lightDirection = vec3(90,0,0);

	lightColor = dot(lightDirection, normalize(norm)) * lightIntensity;
	gl_Position = MVP * vec4(position, 1.0);
}