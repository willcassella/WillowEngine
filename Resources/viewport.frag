#version 330 core

uniform sampler2D positionBuffer;
uniform sampler2D diffuseBuffer;
uniform sampler2D normalBuffer;
uniform sampler2D specularBuffer;
uniform vec3 camPos;
uniform vec3 lightPos;

in vec2 texCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 position = texture(positionBuffer, texCoord).xyz;
	vec3 normal = normalize(texture(normalBuffer, texCoord).xyz);
	
	vec3 surfaceToLight = normalize(lightPos - position);
	vec3 surfaceToCamera = normalize(camPos - position);
	vec3 reflectance = reflect(-surfaceToLight, normal);
	
	float diffuse = max(dot(normal, surfaceToLight), 0);
	float specular = 0;
	
	if (diffuse > 0)
	{
		float specAngle = max(dot(reflectance, surfaceToCamera), 0);
		specular = pow(specAngle, 100);
	}
	
	outColor = texture(diffuseBuffer, texCoord) * (specular + diffuse + 0.2f);
}