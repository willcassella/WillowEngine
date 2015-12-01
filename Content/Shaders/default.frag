// default.frag
#version 430 core

uniform sampler2D diffuse;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fCoord;

out vec4 outColor;

void main()
{
    outColor = texture(diffuse, fCoord);
}
