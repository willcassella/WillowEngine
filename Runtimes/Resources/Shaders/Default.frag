#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D fDiffuse;
float depth = gl_FragDepth;

void main() 
{
	outColor = texture(fDiffuse, Texcoord);
}