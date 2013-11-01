#ifndef STAR_H
#define STAR_H

#include "helpers.h"

class Star
{
public:
    Star(float x, float y, float z, float mass, float R, unsigned int tex);
    void draw();
private:
    float i,o,p,a,n,e,l;
    float x, y, z;
    float mass, R;
    unsigned int tex;
};

#endif // PLANET_H
