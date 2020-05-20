#version 440

uniform sampler2D	texture0;
uniform float brightness;
uniform float contrast;

in vec4 texCoord;

out vec4 FragColor;

//const mat3 coeffsYUV = mat3(0.2126, 0.7152, 0.0722,
//                	-0.09990, -0.3360, 0.4360,
//                	0.6150, -0.5586, -0.0563);

//const mat3 coeffsRGB = mat3(1.0,    0.0,    1.2803,
//                		1.0,    -0.2148,   -0.3805,
//                		1.0,    2.1279,     0.0);

// конструктор матрицы идет по столбцам

const mat3 coeffsYUV = mat3(0.2126, -0.09990, 0.6150,
                	0.7152, -0.3360, -0.5586,
                	0.0722, 0.4360, -0.0563);

const mat3 coeffsRGB = mat3(1.0,    1.0,    1.0,
	               		0.0,    -0.2148,   2.1279,
                		1.2803,    -0.3805,     0.0);

vec3    toYUV(vec3 RGB)
{
    return coeffsYUV * RGB;
}

vec3    toRGB(vec3 YUV)
{
    return coeffsRGB * YUV;
}

void main(void)
{
	vec4 clr = texture2D(texture0, texCoord.xy);

	// contrast
	float factor = 259.0 / 255.0 * (contrast + 255.f)  / (259.f - contrast);

	vec3 color = clr.xyz;
	color = factor * (color - vec3(0.5, 0.5, 0.5)) + vec3(0.5, 0.5, 0.5);
	
	// brightness
	color = toYUV(color);
	float Y = color.x;
	Y = clamp(Y + brightness / 100.f, 0.f, 1.f);
	color.x = Y;
	color = toRGB(color);

	FragColor.xyz = color; // vec3(1.0, 1.0, 1.0);//
	FragColor.w = clr.w;
}
