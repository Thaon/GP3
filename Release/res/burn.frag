#version 330

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform float time;
uniform float burnValue;

in vec2 tex;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy;
    uv.y *= -1;
    
    vec3 pixel = vec3(0.0);
    
    float height = texture(texture_diffuse2 ,uv.xy).r;
    
    pixel = texture(texture_diffuse1,uv.xy).rgb;
    
    
    if((height) < (sin(burnValue + 0.04)) && burnValue > 0)
    {
        pixel = vec3(1,0,0);
    }

    if(height < sin(burnValue))
    {
    	discard;
        pixel = vec3(0,0,0);
    }
  
    if (burnValue >= 1)
		discard;

	fragColor = vec4(pixel,1.0);
}

void main()
{
	gl_FragColor = texture2D(texture_diffuse1, tex);

	mainImage(gl_FragColor, tex);

	if (gl_FragColor.w == 0)
	discard;
}
