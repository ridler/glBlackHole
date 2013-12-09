#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "helpers.h"

class BlackHole
{
public:
    // singular constructor
    BlackHole(float pos[], float R, double mass);
    // constructor for merging
    BlackHole(float pos[], float vel[], float R, double mass);

    void draw(float t, BlackHole* bh, bool mergeMode, unsigned short int dim);

    float mass;
    float R;
    float x, y, z;
    float vx, vy, vz;
};

#endif // BLACKHOLE_H
