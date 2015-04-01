#version 330 core

uniform sampler2D diffuse;

in vec3 fWorldPosition;
in vec3 fWorldNormal;
in vec2 fTexcoord;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out float outSpecular;

void main()
{
	outPosition = fWorldPosition;
	outColor = texture(diffuse, fTexcoord);
	outNormal = fWorldNormal;
}