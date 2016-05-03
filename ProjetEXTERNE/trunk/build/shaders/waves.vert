#version 150

in vec3 position;
in vec3 colour;
in vec2 offset;

uniform mat4 mvp;
uniform float time;
uniform int width;

out vec3 fColour;

float pi = 3.14;
float waveAmplitude = 2.0;
float waveFreq = 1e-3f * 2 * pi;

float distanceFrom(int x, int y) {
    // Returns the distance from the point (x, y) considering the indices of the point.
    float dx = x - offset.x;
    float dy = y - offset.y;
    return sqrt(dx * dx + dy * dy);
}

void addWave(int xSource, int ySource, float amplitude, float frequency, float waveLength) {
    // waveLength unit is (s / indice) so it's not really a waveLengh, but it affects the wave length.
    gl_Position.y += amplitude * cos((time - waveLength * distanceFrom(xSource, ySource)) * frequency);
}

void main(void)
{
    gl_Position = mvp * vec4(position, 1.0);

    int halfWidth = int(width / 2);

    addWave(width, width, waveAmplitude, waveFreq, 100);
    addWave(halfWidth, 0, waveAmplitude * 1.3, waveFreq * 2, 20);
    addWave(0, halfWidth, waveAmplitude * 0.7, waveFreq / 2, 60);

    fColour = colour;
}
