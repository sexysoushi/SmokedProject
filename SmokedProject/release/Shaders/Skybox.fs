#version 130

in vec2 ftc;
//uniform sampler2D t1, t2, t3, t4, t5, t6;
uniform sampler2D texId;

out vec4 gl_FragColor;

void main() {

    gl_FragColor = texture2D(texId, ftc);
}
