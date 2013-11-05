#ifndef STAR_H
#define STAR_H

#include "helpers.h"

class Star
{
public:
    Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex);
    void paint(float t);
private:
    float i,o,p,a,n,e,l;
    float th, ph, rot;
    float x, y, z;
    float mass, R;
    unsigned int tex;
    //void drawSphere(unsigned int texT);
};

#endif // PLANET_H
