#ifndef STAR_H
#define STAR_H

#include "helpers.h"
#include "blackhole.h"

class Star
{
public:
//    Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex);

    void paint(float t, BlackHole* bh, unsigned short int dim, unsigned int texT);

    Star(float x0, float y0, float z0, float v0x, float v0y, float v0z,
               float r, double m);

    float x, y, z;

private:
//    float i,o,p,a,n,e,l;
//    float th, ph, rot;
    float vx, vy, vz;
    float mass, R;
    unsigned int tex;
    bool exists;
};

#endif // PLANET_H
