#include "particlesystem.h"
#include <iostream>

static float world(int px, unsigned short int dim)
{
    float pmin = -dim; float pmax = dim;
    double wx;
    wx = wmin + ((wmax - wmin)/(pmax - pmin))*(px - pmin);
    return wx;
}

ParticleSystem::ParticleSystem(int N, float x0, float y0, float z0, unsigned short int dim)
{
    n = N;
    //x = world(x0, dim); y = world(y0, dim); z = world(z0, dim);

    for(int i = 0; i < n; i++)
    {
        float xx = -1e8 + (float)rand()/((float)1e8);
        float yy = -1e8 + (float)rand()/((float)1e8);
        float zz = -1e8 + (float)rand()/((float)1e8);
        this->particles.push_back(new Particle(x0, y0, z0, xx, yy, zz));
    }
}

void ParticleSystem::update(float t, BlackHole* bh, unsigned short int dim)
{
    for(unsigned short int i = 0; i < particles.size(); i++)
    { particles.at(i)->move(t, bh, dim); }
    //exit(0);
}
