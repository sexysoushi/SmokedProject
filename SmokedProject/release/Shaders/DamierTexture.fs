#version 130


uniform vec4 onColor = vec3(1.0, 1.0, 1.0, 1.0);
uniform vec4 offColor = vec3(0.0, 0.0, 0.0, 1.0);

uniform sampler2D texId;
uniform int numSquaresPerSide = 4;

in vec2 tp; // object-space position

out vec4 fColor;

void main()
{
    float a = step(1.0, mod(tp.x*float(numSquaresPerSide ), 2.0));
    float b = step(1.0, mod(tp.y*float(numSquaresPerSide ), 2.0));
    float f = mod(a+b, 2.0);
    fColor = mix(onColor, offColor, f);
}
