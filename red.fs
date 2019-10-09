#version 330 core

out vec4 color;
uniform float test;
void main()
{
	
	color = vec4(1f, test, 0.f, 0.f);
};
