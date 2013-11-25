#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "helpers.h"
#include "particle.h"
#include <vector>

class ParticleSystem
{
public:
    ParticleSystem(int N, float x0, float y0, float z0, unsigned short dim);
    void update(float t, BlackHole* bh, unsigned short dim);
private:
    int n;              // number of particles
    float x, y, z;      // source position
    std::vector<Particle*> particles;
};

#endif // PARTICLESYSTEM_H
