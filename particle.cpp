#include "particle.h"

Particle::Particle(float x, float y, float z, float v0x, float v0y, float v0z)
{
    this->x = x; this->y = y; this->z = z;
    vx = v0x; vy = v0y; vz = v0z;
    ax = ay = az = 0;
    this->exists = true;
}

void Particle::move(float t, BlackHole* bh)
{
    float M = bh->mass;
    float eH = 0*abs(bh->R);

    if(x <= eH && y <= eH && z <= eH)
    { this->exists = false; }

    if(this->exists)
    {
        ax = -G*M / x*x;
        vx += ax*t;
        x += vx*t + 0.5*ax*t*t;

        ay = -G*M / y*y;
        vy += ay*t;
        y += vy*t + 0.5*ay*t*t;

        az = -G*M / z*z;
        vz += az*t;
        z += vz*t + 0.5*az*t*t;

        glColor3f(1,1,1);
        glBegin(GL_POINT_SPRITE);
        glVertex3f(x, y, z);
        glEnd();
    }
}
