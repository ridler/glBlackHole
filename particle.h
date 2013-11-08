#ifndef PARTICLE_H
#define PARTICLE_H

#include "helpers.h"
#include "blackhole.h"

class Particle
{
public:
    Particle(float x, float y, float z, float v0x, float v0y, float v0z);
    float x, y, z;
    float vx, vy, vz;
    float ax, ay, az;
    bool exists;
    void move(float t, BlackHole* bh);
};

#endif // PARTICLE_H
