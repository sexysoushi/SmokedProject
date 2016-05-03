#version 150

in vec3 position;
in vec3 colour;

uniform mat4 mvp;
out vec3 fColour;

void main(void)
{
    gl_Position = mvp * vec4(position, 1.0);
    fColour = colour;
}
