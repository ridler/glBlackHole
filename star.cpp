#include "star.h"
#include "helperFunctions.h"
#include <iostream>

Star::Star(float pos[], float vel[], float r, double m)
{
    x = pos[0]; y = pos[1]; z = pos[2];
    vx = vel[0]; vy = vel[1]; vz = vel[2];
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
    double denom = pow(x*x + y*y + z*z, 1.5);
    double ax = -G*M*(x)/denom;
    double ay = -G*M*(y)/denom;
    double az = -G*M*(z)/denom;

    vx += ax*t;
    vy += ay*t;
    vz += az*t;

    // Limit velocity to the speed of light
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
