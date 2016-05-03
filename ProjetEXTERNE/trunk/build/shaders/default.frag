#version 150

in vec3 fColour;

out vec4 outColour;

void main(void)
{
    outColour = vec4(fColour, 1.0);
}
