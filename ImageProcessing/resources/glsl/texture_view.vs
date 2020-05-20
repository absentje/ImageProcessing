#version 440

in vec4 vl_VertexPosition;
in vec4 vl_VertexTexCoord0;

out vec4 texCoord;

void main(void)
{
	gl_Position = vec4(vl_VertexPosition.xy, 0.0, 1.0);
	texCoord = vl_VertexTexCoord0;
}