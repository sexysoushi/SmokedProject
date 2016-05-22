#version 130


in vec3 position;
in vec3 velocity;
in float age;

in vec3 color;

uniform float speed;
uniform float gravity;

uniform mat4 MVP;

out vec3 fColor;

const float g = 9.8f; // gravity

void main()
{
  vec3 np;
  np = position+speed*velocity*age;
  np.y -= gravity*age*age;
  gl_Position = MVP * vec4(np, 1.0f );
  gl_PointSize = 4 - age;

  fColor = color;
  fColor.x = 1-age;
  fColor.y = age/2;

}
