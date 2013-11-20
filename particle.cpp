#include "particle.h"
#include <iostream>

Particle::Particle(float x, float y, float z, float v0x, float v0y, float v0z)
{
    this->x = x; this->y = y; this->z = z;
    vx = v0x; vy = v0y; vz = v0z;
    ax = ay = az = 0;
    this->exists = true;
}

static float pixel(float wx, unsigned short int dim)
{
    int pmin = -dim; int pmax = dim;
    float ratio = (pmax - pmin)/(wmax - wmin);
    float result = (wx - wmin)*ratio + pmin;
    return result;
}

void Particle::move(float t, BlackHole* bh, unsigned short int dim)
{
    float M = bh->mass;
    float eH = abs(bh->R);

    if(x <= eH && y <= eH && z <= eH)
    { this->exists = false; return; }

    double denom = pow(x*x + y*y + z*z, 1.5);
    double ax = -G*M*(x)/denom;
    double ay = -G*M*(y)/denom;
    double az = -G*M*(z)/denom;

    vx += ax*t;
    vy += ay*t;
    vz += az*t;

    x += vx*t;
    y += vy*t;
    z += vz*t;

    // Scale real coordinates to screen coordinates:
    float xP = pixel(x, dim);
    float yP = pixel(y, dim);
    float zP = pixel(z, dim);

    std::cout << xP << "\t\t" << yP << "\t\t" << zP << "\t\t" << dim << "\n";

    glEnable(GL_POINT_SPRITE);
    glColor3f(1,1,1);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(xP, yP, zP);
    glEnd();
}
