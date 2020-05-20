#version 440

uniform sampler2D texture;
uniform sampler2D savedScreen;
uniform float ssTime;

in vec4 texCoord;

out vec4 FragColor;

void main(void)
{
	vec4 clr = texture2D(texture, texCoord.xy);
	vec2 tc = texCoord.xy;
	float k = ssTime;// 1 -> 0
	//tc.x = tc.x + k;
	tc.y = tc.y - k;
	float dk = k * 2.0 - 0.5;
	vec4 ssclr = texture2D(savedScreen, tc) * dk * dk * dk;
	if(tc.y > 0.0)
		ssclr = vec4(0.0);

	FragColor = mix(clr, ssclr, ssTime);
}
