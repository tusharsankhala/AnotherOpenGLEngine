#version 330

layout (location=0) in vec3 vPosition;

out vec4 vCol;
uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(vPosition, 1.0f);
	vCol = vec4(clamp(vPosition, 0.0f, 1.0f), 1.0f);
}