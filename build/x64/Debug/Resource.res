        ��  ��                  v   ,   S H A D E R S   ��e     0 	        #version 450 core

out layout (location = 0) vec4 out_color;

void main()
{
    out_color = vec4(0, 0, 1, 1);
}  {   ,   S H A D E R S   ��f     0 	        #version 450 core
in layout (location = 0) vec3 in_position;

void main()
{
    gl_Position = vec4(in_position, 1);
} 