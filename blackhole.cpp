#include "blackhole.h"
#include "helpers.h"

float svec[1];

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
    //glNormal3d(x, y, z);
    glVertex3d(x,y,z);
}

void BlackHole::draw(float t)
{
    glDisable(GL_LIGHTING);
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,svec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    int th,ph;
    glTranslated(this->x, this->y, this->z);
    glScaled(this->R, this->R, this->R);
    //  Latitude bands
    glColor3f(0,0,0);
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
