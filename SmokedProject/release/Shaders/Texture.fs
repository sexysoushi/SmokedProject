#version 140

in vec3 fColor;

uniform sampler2D texId;

out vec4 fragColor;

void main()
{

  fragColor = texture2D(texId, gl_PointCoord);
}
