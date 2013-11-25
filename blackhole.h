#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "helpers.h"

class BlackHole
{
public:
    // singular constructor
    BlackHole(float x, float y, float z, float R, double mass);
    // constructor for merging
    BlackHole(float x, float y, float z, float v0x, float v0y, float v0z,
                         float R, double mass);

    void draw(float t, BlackHole* bh, bool mergeMode, unsigned short int dim);

    float mass;
    float R;
    float x, y, z;
    float vx, vy, vz;
};

#endif // BLACKHOLE_H
