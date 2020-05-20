#version 440

uniform sampler2D	texture0;

in vec4 texCoord;

out vec4 FragColor;

void main(void)
{
	FragColor = texture2D(texture0, texCoord.xy);
}
