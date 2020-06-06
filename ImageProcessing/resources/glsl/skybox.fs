#version 440

uniform samplerCube	skyBox;

in vec3 texCoord;
out vec4 FragColor;

void main(void)
{
	FragColor = texture(skyBox, texCoord);
}
