#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat4 MVP;
uniform float test;
in vec3 v_pos[];



void main(void)
{

vec3 normal = normalize((cross (v_pos[1] - v_pos[0], v_pos[1] - v_pos[2]) ) );

for (int i = 0; i < 3; i++)
	{
	  gl_Position = MVP * vec4(v_pos[i] + abs(test)*normal, 1.0);
	  EmitVertex();
	}
	EndPrimitive();
}

