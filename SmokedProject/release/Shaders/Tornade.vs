#version 130


in vec3 position;
in vec3 velocity;
in float age;

in vec3 color;

uniform float speed;
uniform float gravity;

uniform vec3 down;

uniform mat4 MVP;
uniform mat4 MV;

out vec3 fColor;

const float g = 9.8f; // gravity

void main(void)
{
    float x = cos(speed*age)*sin(age);
    float y = age*2;    
    float z = sin(speed*age)*sin(age);
    
    gl_Position = MVP* vec4(x, y, z, 1.0);
    gl_PointSize = 10.0;

    fColor = color;
    fColor.x = age/2;
    fColor.y = 180*age;
    fColor.z = 180*age+20;

}
