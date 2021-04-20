#version 460

in vec3 vertexIn;
in vec4 colorIn;
in vec2 textureIn;
in vec3 normalIn;

out vec3 vertexOut;
out vec4 colorOut;
out vec3 normalOut;
out vec2 textureOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    // Outputting the same color as 
    colorOut = colorIn;
    normalOut = normalize(normalIn);
    textureOut = textureIn;
    vertexOut = vec3(model * vec4(vertexIn, 1.0));

    gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}