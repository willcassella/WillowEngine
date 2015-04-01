#version 330 core
in vec2 position;
in vec2 vTexCoord;
out vec2 texCoord;
void main()
{
	gl_Position = vec4(position, 0, 1);
	texCoord = vTexCoord;
}