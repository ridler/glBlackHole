#ifndef STAR_H
#define STAR_H

#include "helpers.h"
#include "blackhole.h"

class Star
{
public:
    void paint(float t, BlackHole* bh, unsigned short int dim, unsigned int texT);

    Star(float pos[], float vel[], float r, double m);

    float x, y, z;
    float vx, vy, vz;

private: 
    float mass, R;
    unsigned int tex;
    bool exists;
};

#endif // PLANET_H
