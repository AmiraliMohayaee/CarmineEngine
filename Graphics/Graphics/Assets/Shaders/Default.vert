#version 460

in vec3 vertexIn;
in vec4 colorIn;
in vec2 textureIn;

in vec3 vertexOut;
in vec4 colorOut;
in vec2 textureOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	colorOut = colorIn;
	textureOut = textureIn;

	gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}
