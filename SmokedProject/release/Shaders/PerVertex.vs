#version 130


in vec3 position;
in vec3 velocity;
in float age;

in vec3 color;

uniform float time; //past time
uniform mat4 MVP;

out vec3 fColor;

const float g = 9.8f; // gravity

void main()
{
  vec3 np;
  np = position+0.005*velocity*age;
  np.y -= 0.0000001*g*age*age;
  gl_Position = MVP * vec4(np, 1.0f );
  gl_PointSize = 4 + (200 - age)/1000;

  fColor = color;
  fColor.x = (1500-age)/1500;
}
