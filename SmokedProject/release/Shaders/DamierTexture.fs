#version 130


const vec3 onColor = vec3(1.0, 1.0, 1.0);
const vec3 offColor = vec3(0.0, 0.0, 0.0);

const int numSquaresPerSide = 6;

in vec3 V; // object-space position

out vec4 fColor;

void main()
{
   vec3 NV = normalize(V);
   // Map -1,1 to 0,numSquaresPerSide
   float onOrOff = ((NV.z + 1.0) * float(numSquaresPerSide)) / 2.0;
   // mod 2 >= 1
   onOrOff = step(1.0, mod(onOrOff, 2.0));
   fColor = mix(offColor, onColor, onOrOff);
}