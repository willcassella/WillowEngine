// viewport.frag
#version 430 core

uniform sampler2D positionBuffer;
uniform sampler2D diffuseBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D specularBuffer;

in vec2 fTexCoord;

out vec4 outColor;

void main()
{
    outColor = texture(diffuseBuffer, fTexCoord);
}
