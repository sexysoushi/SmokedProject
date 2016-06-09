#version 130

in vec3 fColor;

uniform sampler2D texId;

out vec4 fragColor;

void main()
{
    float border = 0.02;
    float radius = 0.5;
    vec2 center = vec2(0.5, 0.5);

    vec2 p = gl_PointCoord.xy - center;

    float dist = sqrt(dot(p,p));

    if(dist > radius)
        discard;

    float t = smoothstep(radius+border, radius-border, dist);

    vec4 color = texture2D(texId, gl_PointCoord);
    color.w = 0.2;

    gl_FragColor = mix(vec4(0.0,0.0,0.0,0.0), color, t);
}
