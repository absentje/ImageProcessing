#version 440
uniform sampler2D	texture0;

in vec4 texCoord;
out float FragValue;

float getGray(vec3 c)
{
    return (dot(c.rgb, vec3(0.33333, 0.33333, 0.33333)));
}

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

	float dist = clamp(sqrt(sx * sx + sy * sy), 0.0, 1.0);
	return dist;
}

void main(void)
{
	FragValue = edge_dist(texture0, texCoord.xy);
}
