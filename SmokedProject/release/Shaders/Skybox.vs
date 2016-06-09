#version 130

//in vec2 tCoord_top;
//in vec2 tCoord_front;
//in vec2 tCoord_left;
//in vec2 tCoord_right;
//in vec2 tCoord_bottom;
//in vec2 tCoord_back;

in vec2 tc;

in vec3 position;

uniform mat4 MVP;

out vec2 ftc;


void main() {

    gl_Position = MVP * vec4(position, 1.0f );
    ftc = vec2(gl_MultiTexCoord0);

}
