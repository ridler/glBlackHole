#include "blackhole.h"
#include "helpers.h"

BlackHole::BlackHole(float x, float y, float z, float R, float mass)
{
    this->x = x; this->y = y; this->z = z;
    this->R = R; this->mass = mass;
}

static void bhVertex(int th,int ph)
{
    double x = -Sin(th)*Cos(ph);
    double y =  Cos(th)*Cos(ph);
    double z =          Sin(ph);
    glVertex3d(x,y,z);
}

void BlackHole::draw()
{
    glDisable(GL_LIGHTING);
    int th,ph;
    glTranslated(this->x, this->y, this->z);
    glScaled(this->R, this->R, this->R);
    //  Latitude bands
    glColor3f(1,1,1);
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
    glEnable(GL_LIGHTING);
}
