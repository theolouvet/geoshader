#version 330 core
layout (location = 0) in vec3 pos;

out vec3 v_pos;


uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(pos.x, pos.y, pos.z, 1.0);
    v_pos = pos;
};
