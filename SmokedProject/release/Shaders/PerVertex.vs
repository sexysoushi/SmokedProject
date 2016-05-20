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
  np.y -= 0.5f*g*time*time;
  gl_Position = MVP * vec4(position, 1.0f );
  fColor = color;
}
