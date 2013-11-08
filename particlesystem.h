#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "helpers.h"
#include "particle.h"

class ParticleSystem
{
public:
    ParticleSystem(int N, float x0, float y0, float z0);
private:
    static int n;
    float x, y, z;
    static Particle* particles[];
    void update(float t, BlackHole* bh);
};

#endif // PARTICLESYSTEM_H
