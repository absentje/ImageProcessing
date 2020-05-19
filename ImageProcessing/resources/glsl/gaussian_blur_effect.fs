#version 440

#pragma VL include resources/glsl/include/gaussian.glsl

uniform sampler2D	texture0;
uniform float		sigma;
uniform int 		pipeWidth;
uniform int 		pipeHeight;

in vec4 texCoord;
out vec4 FragColor;

void main(void)
{
	vec2 ctr = texCoord.xy;
	vec2 ds = vec2(1. / pipeWidth, 1. / pipeHeight);

	int boxSize = getGaussianKernelSize(sigma); // либо надо задать (box_size > KernelSize)
	float boxCenter = (float(boxSize) - 1.0) / 2.0;

	float gaussian_sum = 0.0;
	vec4 clr_sum = vec4( 0.0 );
	for (vec2 ij = vec2(0); ij.x < boxSize; ++ij.x)
	{
		for (; ij.y < boxSize; ++ij.y)
		{
			vec2 xy = (ij - boxCenter.xx);
			const vec2 tex_coord = xy * ds + ctr;
			vec4 clr = texture2D( texture0, tex_coord );
			float gaussian_value = Gaussian(sigma, xy.x, xy.y);
			gaussian_sum += gaussian_value;
			clr_sum += gaussian_value * clr;
		}
		ij.y = 0.0;
	}
	FragColor = clr_sum / gaussian_sum;
	FragColor.w = 1.0;
}
