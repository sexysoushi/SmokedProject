#ifndef SAMPLER_H
#define SAMPLER_H

#include "math/vec3.h"

class Sampler
{
public:
     Sampler() {}

     virtual Vec3 getSample() = 0;
};

#endif // SAMPLER_H
