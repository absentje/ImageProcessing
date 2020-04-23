#version 440

uniform sampler2D	texture0;
uniform float highlightDistance;

in vec4 texCoord;
out vec4 FragColor;

float getGray(vec3 c)
{
    return (dot(c.rgb, vec3(0.33333, 0.33333, 0.33333)));
}

const float scale =	10.0;

float edge_dist(sampler2D texture_sampler, vec2 pos)
{
	vec4 CC;
	ivec2 textSize = textureSize(texture_sampler, 0);

	const float width = textSize.x;
	const float height = textSize.y;

	vec2 ox  = vec2(1.0 / width, 0.0);
	vec2 oy  = vec2(0.0, 1.0 / height);
	vec2 UV00 = clamp(pos - ox - oy, 	0.0, 1.0);
	vec2 UV01 = clamp(pos - oy, 		0.0, 1.0);
	vec2 UV02 = clamp(pos + ox - oy, 	0.0, 1.0);
	vec2 UV10 = clamp(pos - ox, 		0.0, 1.0);
	vec2 UV12 = clamp(pos + ox, 		0.0, 1.0);
	vec2 UV20 = clamp(pos - ox + oy, 	0.0, 1.0);
	vec2 UV21 = clamp(pos + oy, 		0.0, 1.0);
	vec2 UV22 = clamp(pos + ox + oy, 	0.0, 1.0);

	CC = texture2D(texture_sampler, UV00); 
	float g00 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV01); 
	float g01 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV02); 
	float g02 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV10); 
	float g10 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV12); 
	float g12 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV20);
	float g20 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV21);
	float g21 = getGray(CC.xyz);

	CC = texture2D(texture_sampler, UV22);
	float g22 = getGray(CC.xyz);

	float sx = 0.0;
	sx -=  g00;
	sx -=  g01 * 2.0;
	sx -=  g02;
	sx +=  g20;
	sx +=  g21 * 2.0;
	sx +=  g22;

	float sy = 0.0;
	sy -=  g00;
	sy +=  g02;
	sy -=  g10 * 2.0;
	sy +=  g12 * 2.0;
	sy -=  g20;
	sy +=  g22;

	float dist = clamp(((sx * sx + sy * sy) * scale), 0.0, 1.0);

	return dist;
}

float max_edge_dist(vec2 pos, ivec2 box_size)
{
	ivec2 textSize = textureSize( texture0, 0 );

	const float width = textSize.x;
	const float height = textSize.y;

	vec2 dr = vec2( 1.0 / width, 1.0 / height ) / 4.0;
	vec2 starting_point = pos - vec2( box_size.x * dr.x, box_size.y * dr.y ) / 2.0;
	float max_dist = 0.0;
	for ( int i = 0; i != box_size.x; ++i )
	{
		for ( int j = 0; j != box_size.y; ++j )
		{
			vec2 cur_iter_point = starting_point + vec2( dr.x * i, dr.y * j );
			float dist = edge_dist( texture0, cur_iter_point );
			max_dist = max( max_dist, dist );
		}
	}
	return max_dist;
}


void main(void)
{
	vec4 clr = texture2D(texture0, texCoord.xy);
	vec3 color = clr.xyz;

	const ivec2 MIN_BOX_SIZE = ivec2( 0, 0 );
	const ivec2 MAX_BOX_SIZE = ivec2( 10, 10 );

	ivec2 box_size = ivec2( 2, 2 );
	float max_dist = max_edge_dist( texCoord.xy, ivec2( mix( MIN_BOX_SIZE, MAX_BOX_SIZE, highlightDistance) ) );

	if (max_dist < 1.0)
	{
		FragColor.xyz = clr.xyz; // vec3( 0.0 );
	}
	else
	{
		FragColor.xyz = vec3( 0.0 );
	}
	FragColor.w = clr.w;
	
}
