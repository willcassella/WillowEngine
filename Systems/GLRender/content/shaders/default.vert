// default.vert
#version 430 core

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vCoord;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fCoord;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1);
	fPosition = (model * vec4(vPosition, 1)).xyz;
	fNormal = (transpose(inverse(model)) * vec4(vNormal, 0)).xyz;
	fCoord = vCoord;
}