#ifndef CONESAMPLER_H
#define CONESAMPLER_H

#include "sampler.h"
#include "math/vec2.h"
#include "math/vec3.h"

class ConeSampler : public Sampler
{
private:
    Vec3 direction;

    // aperture x and y shoud be in [0..2pi[
    Vec2 aperture;

public:
    ConeSampler(Vec3 direction, Vec2 aperture);

    Vec3 getSample();
};

#endif // CONESAMPLER_H
