#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "helpers.h"
#include "particle.h"
#include <vector>

class ParticleSystem
{
public:
    ParticleSystem(int N, float x0, float y0, float z0);
    void update(float t, BlackHole* bh, unsigned short dim);
private:
    int n;
    float x, y, z;
    std::vector<Particle*> particles;
};

#endif // PARTICLESYSTEM_H
