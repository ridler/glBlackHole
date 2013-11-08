#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "helpers.h"
#include "particle.h"

class ParticleSystem
{
public:
    ParticleSystem(int N, float x0, float y0, float z0);
    void update(float t, BlackHole* bh);
private:
    int n;
    float x, y, z;
    Particle* particles[];
};

#endif // PARTICLESYSTEM_H
