#version 330

out vec4 outColour;

in vec2 passTexCoords;
in vec3 passColour; 

void main()
{
	outColour = vec4(passColour, 1.0);
}	

