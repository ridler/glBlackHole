#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "helpers.h"

class BlackHole
{
public:
    BlackHole(float x, float y, float z, float R, double mass);
    void draw(float t);
    float mass;
    float R;
    float x, y, z;
};

#endif // BLACKHOLE_H
