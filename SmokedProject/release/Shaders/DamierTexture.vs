#version 130


uniform mat4 MVP;

in vec3 position;
in vec2 tc;

out vec2 tp;


void main()
{
  gl_Position = MVP * vec4( position, 1.0f );

  tp = tc;
}
