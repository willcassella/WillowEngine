// default.frag
#version 430 core

uniform sampler2D diffuse;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fCoord;

layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec4 outDiffuse;
layout (location = 2) out vec3 outNormal;
layout (location = 3) out vec4 outSpecular;

void main()
{
    outDiffuse = texture(diffuse, fCoord);
}
