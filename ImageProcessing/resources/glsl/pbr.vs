#version 440
#pragma VL include resources/glsl/std/uniforms.glsl
#pragma VL include resources/glsl/std/vertex_attribs.glsl

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

void main(void)
{
	gl_Position = vl_ModelViewProjectionMatrix * vl_VertexPosition;
	TexCoords = vl_VertexTexCoord0.xy;
	WorldPos = (vl_WorldMatrix * vl_VertexPosition).xyz;
	Normal = normalize( vl_NormalMatrix * vl_VertexNormal );
}  