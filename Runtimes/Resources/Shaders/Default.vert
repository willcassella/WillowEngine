#version 330 core
in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;
out vec3 Position;
out vec3 Normal;
out vec2 Texcoord;
uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;
void main() 
{
	gl_Position = vProjection * vView * vModel * vec4(vPosition, 1.0);
	Texcoord = vec2(vTexcoord.x, 1.0 - vTexcoord.y);
	Position = vPosition;
	Normal = vNormal;
}