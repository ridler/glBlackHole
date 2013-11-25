#include "blackhole.h"
#include "helpers.h"

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

// convert from real coordinates to screen coordinates
static float pixel(float wx, unsigned short int dim)
{
    int pmin = -dim; int pmax = dim;
    float ratio = (pmax - pmin)/(wmax - wmin);
    float result = (wx - wmin)*ratio + pmin;
    return result;
}

static void bhVertex(int th,int ph)
{
    float x = -Sin(th)*Cos(ph);
    float y =  Cos(th)*Cos(ph);
    float z =          Sin(ph);
    glNormal3f(x, y, z);
    glVertex3f(x,y,z);
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
        float ax = G*M/(rx*rx);
        float ay = G*M/(ry*ry);
        float az = G*M/(rz*rz);

//        double denom = pow(x*x + y*y + z*z, 1.5);
//        double ax = G*M*(rx)/denom;
//        double ay = G*M*(ry)/denom;
//        double az = G*M*(rz)/denom;

        vx += ax*t;
        vy += ay*t;
        vz += az*t;

        vx > 3e8 ? vx = 3e8 : vx = vx;
        vy > 3e8 ? vy = 3e8 : vy = vy;
        vz > 3e8 ? vz = 3e8 : vz = vz;

        x += ax*t*t + vx*t;
        y += ay*t*t + vy*t;
        z += az*t*t + vz*t;
    }

    float rP = pixel(R, dim);
    float xP = pixel(x, dim); float yP = pixel(y, dim); float zP = pixel(z, dim);
    int th,ph;

    glTranslated(xP, yP, zP);

    glScaled(rP, rP, rP);
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
