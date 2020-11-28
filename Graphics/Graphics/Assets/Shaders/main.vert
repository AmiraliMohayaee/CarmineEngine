#version 460


in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    // Outputting the same color as 
    colorOut = colorIn;

    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}