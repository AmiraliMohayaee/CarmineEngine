#version 460

in vec3 vertexOut;
in vec4 colorOut;
in vec2 textureOut;

out vec4 pixelColor;

uniform bool isTextured;
uniform sampler2D textureImage;

void main(void)
{

	if (isTextured)
	{
		vec2 uv;
		uv.x = textureOut.x;
		uv.y = 1 - textureOut.y;
		pixelColor = colorOut * texture(textureImage, uv);
	}

	else
	{
		pixelColor = colorOut;
	}


}