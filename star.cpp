#include "star.h"

const float G = 6.67e-11;
const float RADSCALE = 1e5;
const float EMISS = 0;
float shinyvec[1];    // Shininess (value)
float yellow[] = {1.0,1.0,0.0,1.0};
float Emission[]  = {0.0,0.0,0.01*EMISS,1.0};

Star::Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex)
{
    this->R = G*R;  //  Radius (km->AU)
    this->x = pos[0]; this->y = pos[1]; this->z = pos[2];
    this->mass = m; this->tex = tex;
    this->rot = mot[0]; this->th = mot[1]; this->ph = mot[2];
    this->i = kep[0];
    this->o = kep[1];
    this->p = kep[2];
    this->a = kep[3];
    this->n = kep[4];
    this->e = kep[5];
    this->l = kep[6];
}

static void starVertex(int th,int ph)
{
    double x = -Sin(th)*Cos(ph);
    double y =  Cos(th)*Cos(ph);
    double z =          Sin(ph);
    glNormal3d(x,y,z);
    //glTexCoord2d(th/360.0,ph/180.0+0.5);
    glVertex3d(x,y,z);
}

static void drawSphere(unsigned int texT)
{
    int th,ph;
    glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    //  Set texture
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,texT);
    glColor3f(1,0,0);
    //  Latitude bands
    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=5)
        {
            starVertex(th,ph);
            starVertex(th,ph+5);
        }
        glEnd();
    }
}

void Star::paint(float t)
{
    //  Apply keplerian elements to determine orbit
    //  Calculate true anomaly
    float M = fmod(t*n+l-p,2*M_PI); //  Mean anomaly in radians
    float delta = 0;
    float v = M;

    while (fabs(delta)>1e-12)
    {
        delta = v - e*sin(v) - M;
        v -= delta/(1-e*cos(v));
    }

    //  True anomaly
    v = 2*atan(sqrt((1+e)/(1-e))*tan(0.5*v));
    float oR = a*(1-e*e)/(1+e*cos(v));  //  Orbit radius (AU)
    float h = v + p - o;                //  Elliptical angle

    //  Compute and apply location
    this->x = oR * (cos(o)*cos(h) - sin(o)*sin(h)*cos(i));
    this->y = oR * (sin(o)*cos(h) + cos(o)*sin(h)*cos(i));
    this->z = oR *                        (sin(h)*sin(i));

    //  Transform and draw planet
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(th,1,0,0);            //  Declination
    glRotated(360*t/rot,0,0,1);     //  Siderial rotation
    this->R *= RADSCALE;
    glScaled(R,R,R);
    drawSphere(this->tex);
    glPopMatrix();
}
