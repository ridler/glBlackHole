#ifndef STAR_H
#define STAR_H

#include "helpers.h"

class Star
{
public:
    Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex);
    void paint(float t);
    float x, y, z;

private:
    float i,o,p,a,n,e,l;
    float th, ph, rot;
    float mass, R;
    unsigned int tex;
    //void drawSphere(unsigned int texT);
};

#endif // PLANET_H
