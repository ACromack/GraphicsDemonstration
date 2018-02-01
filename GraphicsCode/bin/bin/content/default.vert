#version 440 core

layout (location = 0) in vec3 Pos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(Pos.x, Pos.y, Pos.z, 1.0);

}