// viewport.frag
#version 430 core

uniform sampler2D diffuse;

in vec2 fTexCoord;

out vec4 outColor;

void main()
{
    outColor = texture(diffuse, fTexCoord);
}
