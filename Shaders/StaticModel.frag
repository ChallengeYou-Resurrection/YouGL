#version 330

out vec4 outColour;


in vec3 passTexCoord;
in vec3 passColour; 

uniform sampler2DArray textureArray;

void main()
{
	outColour = texture(textureArray, passTexCoord) * vec4(passColour, 1.0);
}	

