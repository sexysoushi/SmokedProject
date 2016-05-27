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

void main()
{

    vec3 np;
    // initial velocity * time
    np = position + speed * velocity * age * 10;

    // gravity following down vector
    np = np + down * gravity * age * age;

    gl_Position = MVP * vec4(np, 1.0f );

    gl_PointSize = (30*age)/10;

    fColor = color;
    fColor.x = 270*age;
    fColor.y = age / 2;

}
