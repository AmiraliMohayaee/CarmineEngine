#version 460

in vec3 colorOut;
in vec2 textureOut;
out vec4 pixelColor;

uniform bool isTextured;
uniform sampler2D textureImage;

void main(void) 
{
	if(isTextured)
	{
		pixelColor = vec4(colorOut, 1.0) * texture(textureImage, textureOut);
	}

	else
	{
		pixelColor = vec4(colorOut, 1.0);
	}
}