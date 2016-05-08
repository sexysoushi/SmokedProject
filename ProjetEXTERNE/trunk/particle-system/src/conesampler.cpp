#include "conesampler.h"

ConeSampler::ConeSampler(Vec3 direction, Vec2 aperture)
    : direction(direction), aperture(aperture)
{}

Vec3 ConeSampler::getSample() {
    direction.normalize();

    Vec2 coords = direction.sphericalCoord();

    Vec2 halfAperture = aperture / 2.0;

    float maxa1 = coords.x + halfAperture.x;
    float mina1 = coords.x - halfAperture.x;
    float maxa2 = coords.y + halfAperture.y;
    float mina2 = coords.y - halfAperture.y;

    float a1 = rand_0_1() * (maxa1 - mina1) + mina1;
    float a2 = rand_0_1() * (maxa2 - mina2) + mina2;

    float x = cos(a1) * cos(a2);
    float y = cos(a1) * sin(a2);
    float z = sin(a1);

    Vec3 sample(x, y, z);

    return sample;
}
