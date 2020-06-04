#version 440

#pragma VL include resources/glsl/std/uniforms.glsl
#pragma VL include resources/glsl/std/vertex_attribs.glsl

out vec4 texCoord;

void main(void)
{
	vec4 pos = vl_ModelViewProjectionMatrix * vl_VertexPosition;

	gl_Position = pos;
	texCoord = vl_VertexTexCoord0;
}