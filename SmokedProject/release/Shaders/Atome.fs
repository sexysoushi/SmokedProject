#version 130


in vec3 fColor;
uniform sampler2D texId;
out vec4 fragColor;


void main()
{
    vec4 color = texture2D(texId, gl_PointCoord);
    if(color.x > 0.9 && color.y > 0.9 && color.z > 0.9)
        discard;
    else
        fragColor = color;
}
