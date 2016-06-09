#version 130


in vec3 position;
in vec3 velocity;
in float age;

in vec3 color;

uniform float speed;
uniform float gravity;
uniform float size;
uniform vec3 down;

uniform mat4 MVP;

out vec3 fColor;
out float fAge;

const float g = 9.8f; // gravity

void main()
{

    vec3 np;
    // initial velocity * time
    np = position + speed * velocity * age;

    // gravity following down vector
    np = np + down * gravity * age * age;

    gl_Position = MVP * vec4(np, 1.0f );

    gl_PointSize = (10 - 2*age) * size;

    fColor = color;
    fColor.x = 4 - age;
    fColor.y = age / 2;

    fAge = age;

}
