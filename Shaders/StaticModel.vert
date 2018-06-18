#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inTexCoord;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec3 inColour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;


out vec3 passTexCoord;
out vec3 passColour;

// Temp Lighting Variables
vec3 light_Position = vec3(100.0, 400.0, 400.0);
vec3 light_Color = vec3(0.7, 0.78, 0.7);

void main()
{
	vec4 world_position = modelMatrix * vec4(inVertexPosition, 1.0);
	gl_Position = projMatrix * viewMatrix * world_position;

	vec3 diffuse;

	vec3 surfaceNormal   = (modelMatrix * vec4(inNormal, 0.0)).xyz;
	vec3 unitNormal      = normalize(surfaceNormal);

	vec3 toCameraVector  = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - world_position.xyz;
	vec3 lightDirection  = normalize(light_Position - world_position.xyz);
	vec3 cameraDirection = normalize(toCameraVector);

	diffuse  = light_Color * max(0.3, dot(unitNormal, lightDirection)) + vec3(0.3, 0.3, 0.3);
	diffuse *= inColour;

	passTexCoord = inTexCoord;
	passColour = diffuse;
}