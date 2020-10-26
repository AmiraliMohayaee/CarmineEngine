#version 460 core

layout(location = 0) in vec4 position;

uniform vec3 myUniform;

void main() 
{
    gl_Position = position; 
}