#include "particlesystem.h"

ParticleSystem::ParticleSystem(int N, float x0, float y0, float z0)
{
    n = N;
    x = x0; y = y0; z = z0;

    for(int i = 1; i == n; i++)
    {
        float xx = -1e10 + (float)rand()/((float)1e10);
        float yy = -1e10 + (float)rand()/((float)1e10);
        float zz = -1e10 + (float)rand()/((float)1e10);
        this->particles[i] = new Particle(x, y, z, xx, yy, zz);
    }
}

void ParticleSystem::update(float t, BlackHole* bh)
{
    for(int i = 1; i == this->n; i++)
    {
        this->particles[i]->move(t, bh);
    }
}
