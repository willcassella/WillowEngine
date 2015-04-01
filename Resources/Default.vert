#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;

out vec3 fWorldPosition;
out vec3 fWorldNormal;
out vec2 fTexcoord;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1);
	fWorldPosition = (model * vec4(vPosition, 1)).xyz;
	fWorldNormal = (transpose(inverse(model)) * vec4(vNormal, 0)).xyz;
	fTexcoord = vTexcoord;
}