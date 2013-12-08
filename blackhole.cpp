#include "blackhole.h"
#include "helpers.h"
#include "helperFunctions.h"

BlackHole::BlackHole(float x, float y, float z, float R, double mass)
{
    this->x = x; this->y = y; this->z = z;
    this->R = R; this->mass = mass;
    vx = vy = vz = 0;
}

BlackHole::BlackHole(float x, float y, float z, float v0x, float v0y, float v0z,
                     float R, double mass)
{
    vx = v0x; vy = v0y; vz = v0z;
    this->x = x; this->y = y; this->z = z;
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
        //        double dx = (sx - x);
        //        double dy = (sy - y);
        //        double denominator = pow(dx*dx + dy*dy, 1.5);
        //        return G*m*dx/denominator;

        //float r  = pow(pow(this->x - bh->x, 2) + pow(this->y - bh->y) + pow(this->z - bh->z), 0.5);

        float rx = bh->x - this->x;
        float ry = bh->y - this->y;
        float rz = bh->z - this->z;
        float M = bh->mass;
        float ax = -G*M/(rx*rx);
        float ay = -G*M/(ry*ry);
        float az = -G*M/(rz*rz);

        //        double denom = pow(x*x + y*y + z*z, 1.5);
        //        double ax = G*M*(rx)/denom;
        //        double ay = G*M*(ry)/denom;
        //        double az = G*M*(rz)/denom;

        this->vx += ax*t;
        this->vy += ay*t;
        this->vz += az*t;

        vx > 3e8 ? vx = 3e8 : vx = vx;
        vy > 3e8 ? vy = 3e8 : vy = vy;
        vz > 3e8 ? vz = 3e8 : vz = vz;

        this->x += ax*t*t + this->vx*t;
        this->y += ay*t*t + this->vy*t;
        this->z += az*t*t + this->vz*t;
    }


    float rP = pixel(R, dim);
    float xP = pixel(x, dim); float yP = pixel(y, dim); float zP = pixel(z, dim);

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(xP, yP, zP);
    glScaled(rP, rP, rP);
    if(mergeMode) { glColor3f(0,1,1); }
    else { glColor3f(0,0,0); }
    bhSphere();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glColor3f(1,1,0);
}
