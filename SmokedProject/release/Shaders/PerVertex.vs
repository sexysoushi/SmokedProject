#version 130


in vec3 position;
in vec3 velocity;
in vec3 color;

uniform float time; //past time
uniform mat4 MVP;

out vec3 fColor;

const float g = 9.8f; // gravity

void main()
{
  vec3 np;
  np = position+velocity*time;
  np.y -= 10*g*time*time;
  np.x += 5*time;
  gl_Position = MVP * vec4(np, 1.0f );
  gl_PointSize = 4.0f;
  fColor = color;
}
