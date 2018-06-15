#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec3 inColour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec2 passTexCoord;
out vec3 passColour;

void main()
{
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);

	passTexCoord = inTexCoord;
	passColour = inColour;
}