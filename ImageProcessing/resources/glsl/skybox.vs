#version 440

#pragma VL include resources/glsl/std/uniforms.glsl
#pragma VL include resources/glsl/std/vertex_attribs.glsl

out vec3 texCoord;

void main(void)
{
	gl_Position = vl_ProjectionMatrix * vec4( vl_NormalMatrix * vl_VertexPosition.xyz, 1.0 );
	gl_Position = gl_Position.xyww;

	texCoord = vl_VertexPosition.xyz;
}