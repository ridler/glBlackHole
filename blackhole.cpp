#include "blackhole.h"
#include "helpers.h"

BlackHole::BlackHole(float x, float y, float z, float R, double mass)
{
    this->x = x; this->y = y; this->z = z;
    this->R = R; this->mass = mass;
}

static void bhVertex(int th,int ph)
{
    float x = -Sin(th)*Cos(ph);
    float y =  Cos(th)*Cos(ph);
    float z =          Sin(ph);
    glNormal3f(x, y, z);
    glVertex3f(x,y,z);
}

void BlackHole::draw(float t)
{
    //glDisable(GL_LIGHTING);
    int th,ph;
    glTranslated(this->x, this->y, this->z);
    glScaled(R*rScale, R*rScale, R*rScale);
    //  Latitude bands
    glColor3f(1,0,1);
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
   // glEnable(GL_LIGHTING);
}
