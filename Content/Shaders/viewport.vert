// viewport.vert
#version 330 core

in vec2 vPosition;
in vec2 vTexCoord;

out vec2 fTexCoord;

void main()
{
	gl_Position = vec4(vPosition, 0, 1);
	fTexCoord = vTexCoord;
}