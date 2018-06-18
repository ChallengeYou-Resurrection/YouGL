#version 330

out vec4 outColour;

in vec3 passTexCoords;
in vec3 passColour; 

uniform sampler2DArray textureArray;

void main()
{
	outColour = texture(textureArray, passTexCoords) * vec4(passColour, 1.0);
}	

