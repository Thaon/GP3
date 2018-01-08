#version 330

uniform sampler2D texture_diffuse1;

in vec2 tex;
in vec4 col;
in vec3 cameraPos;
in vec3 vertexPos;

in float lightColor;

out vec4 fragCol;

void main()
{
	float colInt = lightColor;
	vec4 color;
	vec2 uv = tex.xy;

	if (colInt > 0.95)
		color = vec4(0.5,0.5,0.5,1.0);
	else if (colInt > 0.5)
		color = vec4(0.3,0.3,0.3,1.0);
	else if (colInt > 0.25)
		color = vec4(0.2,0.2,0.2,1.0);
	else
		color = vec4(0.1,0.1,0.1,1.0);


	fragCol = color * texture2D(texture_diffuse1, uv.xy);
}