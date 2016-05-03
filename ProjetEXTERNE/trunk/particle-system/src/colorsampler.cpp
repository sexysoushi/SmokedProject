#include "colorsampler.h"

ColorSampler::ColorSampler() {}

Color ColorSampler::getSample() {
    float r, g, b;

    // random pastel colors
    r = (rand_0_1() * 128) + 100;
    g = (rand_0_1() * 128) + 100;
    b = (rand_0_1() * 128) + 100;

    Color c(r, g, b);

    return c / 255.0;
}
