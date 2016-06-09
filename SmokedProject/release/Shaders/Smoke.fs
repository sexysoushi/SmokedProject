#version 130

uniform sampler2D texId;

in vec3 fColor;
in float fAge;

out vec4 fragColor;


void main()
{
    vec4 color = texture2D(texId, gl_PointCoord);
    if(color.w > 0.1){
        color.w = 0.5 * (5-fAge)/5;
        gl_FragColor = color;
    }
    else
        discard;
}
