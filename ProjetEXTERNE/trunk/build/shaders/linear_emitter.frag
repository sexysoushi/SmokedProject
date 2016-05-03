#version 150

in vec3 fColor0;

out vec4 outColor;

uniform sampler2D tex;

void main(void)
{
    vec2 texcoord = vec2 (gl_PointCoord.s, 1.0 - gl_PointCoord.t);
    vec4 texel = texture(tex, texcoord);
    outColor = vec4(texel.rgb * fColor0, texel.a);
}
