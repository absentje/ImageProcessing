#version 440

#pragma VL include resources/glsl/include/gaussian.glsl

uniform sampler2D	texture0;
uniform sampler2D	sobel_distance_texture;
uniform float		sigma;
uniform int 		pipeWidth;
uniform int 		pipeHeight;
uniform bool		isColorful;

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
	vec2 ds = vec2(1. / pipeWidth, 1. / pipeHeight);

	int boxSize = getGaussianKernelSize(sigma); // либо надо задать (box_size > KernelSize)
	float boxCenter = (float(boxSize) - 1.0) / 2.0;

	float gaussian_sum = 0.0;
	float dist_value_sum = 0.0;
	for (vec2 ij = vec2(0); ij.x < boxSize; ++ij.x)
	{
		for (; ij.y < boxSize; ++ij.y)
		{
			vec2 xy = (ij - boxCenter.xx);
			const vec2 tex_coord = xy * ds + ctr;
			float dist = clamp( texture2D( sobel_distance_texture, tex_coord ).r, 0.0, 1.0 );
			dist = 1. - float(dist >= 1.0);
			float gaussian_value = Gaussian(sigma, xy.x, xy.y);
			gaussian_sum += gaussian_value;
			dist_value_sum += gaussian_value * dist;
		}
		ij.y = 0.0;
	}
	FragColor = vec4( dist_value_sum / gaussian_sum );
	if (isColorful)
		FragColor *= clr;
	FragColor.w = 1.0;
}
