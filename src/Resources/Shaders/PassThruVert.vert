#version 450 core
in layout (location = 0) vec3 in_position;

void main()
{
    gl_Position = vec4(in_position, 1);
}