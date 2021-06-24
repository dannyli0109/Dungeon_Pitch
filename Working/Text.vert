#version 450

layout (location = 0) in vec4 a_Vertex; // <vec2 pos, vec2 tex>
out vec2 v_Uv;

uniform mat4 u_ProjectionMatrix;

void main()
{
	gl_Position = u_ProjectionMatrix * vec4(a_Vertex.xy, 0.0, 1.0);
	v_Uv = a_Vertex.zw;
}
