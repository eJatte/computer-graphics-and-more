#version 330 core

layout (location = 0) in vec4 v_coord;

void main()
{
    gl_Position = vec4(v_coord.x, v_coord.y, v_coord.z, 1.0);
}