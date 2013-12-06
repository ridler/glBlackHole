#include "star.h"
#include "helperFunctions.h"
#include <iostream>

//const float EMISS = 16;
//float shinyvec[1];    // Shininess (value)
//float yellow[] = {1.0,1.0,0.0,1.0};
//float Emission[]  = {0.0,0.0,0.01*EMISS,1.0};

Star::Star(float x0, float y0, float z0, float v0x, float v0y, float v0z,
           float r, double m)
{
    x = x0; y = y0; z = z0;
    vx = v0x; vy = v0y; vz = v0z;
    R = r; mass = m;
    exists = true;
}

void Star::paint(float t, BlackHole* bh, unsigned short dim, unsigned int texT)
{
    // If the star gets inside the event horizon, it will no longer exist
    float eh = bh->R;
    if (x <= abs(eh) && y <= abs(eh) && z <= abs(eh))
    { this->exists = false; return; }

    // Newtonian force calculations:
    double M = bh->mass;

    //std::cout << "M = " << M << "\t" << "R = " << eh << "\n";

    double denom = pow(x*x + y*y + z*z, 1.5);
    double ax = -G*M*(x)/denom;
    double ay = -G*M*(y)/denom;
    double az = -G*M*(z)/denom;

    vx += ax*t;
    vy += ay*t;
    vz += az*t;

    vx > 3e8 ? vx = 3e8 : vx = vx;
    vy > 3e8 ? vy = 3e8 : vy = vy;
    vz > 3e8 ? vz = 3e8 : vz = vz;

    x += vx*t;
    y += vy*t;
    z += vz*t;

    // Scale real coordinates to screen coordinates:
    float xP = pixel(x, dim);
    float yP = pixel(y, dim);
    float zP = pixel(z, dim);

    float rP = pixel(this->R, dim);

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslated(xP, yP, zP);
    glScaled(rP, rP, rP);
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    billboardBegin();
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glPopMatrix();
}
