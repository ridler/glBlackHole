#include "blackhole.h"
#include "helpers.h"
#include "helperFunctions.h"

BlackHole::BlackHole(float pos[], float R, double mass)
{
    this->x = pos[0]; this->y = pos[1]; this->z = pos[2];
    this->R = R; this->mass = mass;
    vx = vy = vz = 0;
}

BlackHole::BlackHole(float pos[], float vel[], float R, double mass)
{
    vx = vel[0]; vy = vel[1]; vz = vel[2];
    this->x = pos[0]; this->y = pos[1]; this->z = pos[2];
    this->R = R; this->mass = mass;
}

static void bhVertex(int th,int ph)
{
    float x = -Sin(th)*Cos(ph);
    float y =  Cos(th)*Cos(ph);
    float z =          Sin(ph);
    glVertex3f(x,y,z);
}

static void bhSphere()
{
    short int th,ph;
    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=5)
        {
            bhVertex(th,ph);
            bhVertex(th,ph+5);
        }
        glEnd();
    }
}

void BlackHole::draw(float t, BlackHole* bh, bool mergeMode, unsigned short int dim)
{
    if (mergeMode)
    {
        float rx = bh->x - this->x;
        float ry = bh->y - this->y;
        float rz = bh->z - this->z;

        float M = bh->mass;

        double denom = pow(rx*rx + ry*ry + rz*rz, 1.5);
        double ax = G*M*(rx)/denom;
        double ay = G*M*(ry)/denom;
        double az = G*M*(rz)/denom;

        this->vx += ax*t;
        this->vy += ay*t;
        this->vz += az*t;

        // Limit velocities to speed of light
        vx > 3e8 ? vx = 3e8 : vx = vx;
        vy > 3e8 ? vy = 3e8 : vy = vy;
        vz > 3e8 ? vz = 3e8 : vz = vz;

        this->x += this->vx*t;
        this->y += this->vy*t;
        this->z += this->vz*t;
    }


    float rP = pixel(R, dim);
    float xP = pixel(x, dim);
    float yP = pixel(y, dim);
    float zP = pixel(z, dim);

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(xP, yP, zP);
    glScaled(rP, rP, rP);
    if(mergeMode) { glColor3f(0,1,1); }
    else { glColor3f(0,0,0); }
    bhSphere();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
