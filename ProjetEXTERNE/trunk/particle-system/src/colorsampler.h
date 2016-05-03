#ifndef COLORSAMPLER_H
#define COLORSAMPLER_H

#include "color.h"
#include "sampler.h"

class ColorSampler : public Sampler
{
public:
    ColorSampler();

    Color getSample();
};

#endif // COLORSAMPLER_H
