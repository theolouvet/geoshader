#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;

uniform mat4 MVP;
uniform float test;
in vec3 v_pos[];

void main(void)
{

vec3 normal = normalize((cross (v_pos[1] - v_pos[0], v_pos[1] - v_pos[2]) ) );
	vec3 mid = v_pos[2] + v_pos[1] + v_pos[0];
	gl_Position = MVP * vec4(normal *0.05 + mid/3., 1.0) ;
        EmitVertex();
	gl_Position = MVP * vec4(mid/3., 1.0) ;
	EmitVertex();
	EndPrimitive();
}


