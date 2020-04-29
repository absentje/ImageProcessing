#version 440

uniform sampler2D	texture0;
uniform sampler2D	sobel_distance_texture;
uniform float		highlightDistance;

in vec4 texCoord;
out vec4 FragColor;

const float step = 0.001;
const float PI =  3.141592653;
const float TWO_PI = PI * 2.0;

vec2 direction(float angle)
{
	return vec2(cos(angle), sin(angle));
}

void main(void)
{
	vec2 ctr = texCoord.xy;
	vec4 clr = texture2D( texture0, ctr );

	int radius = 0; 
	const int MAX_RADIUS = int(mix( 0.0, 10.0, highlightDistance ));
	const int DIRECTIONS_COUNT = 8;
	vec2 directions[DIRECTIONS_COUNT];
	float dfi = TWO_PI / DIRECTIONS_COUNT;
	for (int i = 0; i != DIRECTIONS_COUNT; ++i)
	{
		directions[i] = direction(dfi * i);
	}

	int min_radius = 1000;
	for (; radius < MAX_RADIUS; ++radius)
	{
		for (int i = 0; i != DIRECTIONS_COUNT; ++i)
		{
			float dist = texture2D( sobel_distance_texture, ctr + step * radius * directions[i] ).r;
			if ( dist >= 1.0 )
			{
				min_radius = min( min_radius, radius );
			}
		}
	}

	float shadow_coef = clamp(float(min_radius) / MAX_RADIUS, 0.0, 1.0);

	float val = mix( 0.15, 1.0, shadow_coef );

	FragColor.xyz = clr.xyz * val;

	FragColor.w = clr.w;
}
