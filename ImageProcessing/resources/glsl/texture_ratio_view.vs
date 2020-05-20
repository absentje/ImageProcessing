#version 440

uniform vec2 screen_Size;
uniform vec2 texture_Size;

in vec4 vl_VertexPosition;
in vec4 vl_VertexTexCoord0;

out vec4 texCoord;

void main(void)
{
	float s_wh = screen_Size.x / screen_Size.y;
	float t_wh = texture_Size.x / texture_Size.y;

	float maxST = max(s_wh, t_wh);
	float dx = t_wh / maxST;
	float dy = s_wh / maxST;

	gl_Position = vec4(dx * vl_VertexPosition.x, dy * vl_VertexPosition.y, 0.0, 1.0);
	texCoord = vl_VertexTexCoord0;
}