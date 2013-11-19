#include "star.h"
#include <iostream>

const float EMISS = 0;
float shinyvec[1];    // Shininess (value)
float yellow[] = {1.0,1.0,0.0,1.0};
float Emission[]  = {0.0,0.0,0.01*EMISS,1.0};

Star::Star(float x0, float y0, float z0, float v0x, float v0y, float v0z,
           float r, double m, unsigned int texT)
{
    x = x0; y = y0; z = z0;
    vx = v0x; vy = v0y; vz = v0z;
    R = r; mass = m;
    tex = texT; exists = true;
}

//Star::Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex)
//{
//    this->R = G*R;  //  Radius (km->AU)
//    this->x = pos[0]; this->y = pos[1]; this->z = pos[2];
//    this->mass = m; this->tex = tex;
//    this->rot = mot[0]; this->th = mot[1]; this->ph = mot[2];
//    this->i = kep[0];
//    this->o = kep[1];
//    this->p = kep[2];
//    this->a = kep[3];
//    this->n = kep[4];
//    this->e = kep[5];
//    this->l = kep[6];
//}

static float pixel(float wx, unsigned short int dim)
{
    int pmin = -dim; int pmax = dim;
    float ratio = (pmax - pmin)/(wmax - wmin);
    float result = (wx - wmin)*ratio + pmin;
    return result;
}

static void starVertex(int th,int ph)
{
    float x = -Sin(th)*Cos(ph);
    float y =  Cos(th)*Cos(ph);
    float z =          Sin(ph);
    glNormal3f(x,y,z);
    //glTexCoord2d(th/360.0,ph/180.0+0.5);
    glVertex3f(x,y,z);
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

void Star::paint(float t, BlackHole* bh, unsigned short dim)
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

//    float ax, ay, az;
//    double M = bh->mass;

//    ax = -G*M / x*x;
//    vx += ax*t;
//    x += vx*t + 0.5*ax*t*t;

//    ay = -G*M / y*y;
//    vy += ay*t;
//    y += vy*t + 0.5*ay*t*t;

//    az = -G*M / z*z;
//    vz += az*t;
//    z += vz*t + 0.5*az*t*t;

//    float xP = x*pScale; float yP = y*pScale; float zP = z*pScale;
//    float rP = R*rScale;

    std::cout << xP << "\t\t" << yP << "\t\t" << zP << "\n";

    glPushMatrix();
    glTranslated(xP, yP, zP);
    glScaled(rP, rP, rP);
    drawSphere(0);
    glPopMatrix();

//    //  Apply keplerian elements to determine orbit
//    //  Calculate true anomaly
//    float M = fmod(t*n+l-p,2*M_PI); //  Mean anomaly in radians
//    float delta = 0;
//    float v = M;

//    while (fabs(delta)>1e-12)
//    {
//        delta = v - e*sin(v) - M;
//        v -= delta/(1-e*cos(v));
//    }

//    //  True anomaly
//    v = 2*atan(sqrt((1+e)/(1-e))*tan(0.5*v));
//    float oR = a*(1-e*e)/(1+e*cos(v));  //  Orbit radius (AU)
//    float h = v + p - o;                //  Elliptical angle

//    //  Compute and apply location
//    this->x = oR * (cos(o)*cos(h) - sin(o)*sin(h)*cos(i));
//    this->y = oR * (sin(o)*cos(h) + cos(o)*sin(h)*cos(i));
//    this->z = oR *                        (sin(h)*sin(i));

//    //  Transform and draw planet
//    glPushMatrix();

//    glTranslated(x, y, z);
//    glRotated(th,1,0,0);            //  Declination
//    glRotated(360*t/rot,0,0,1);     //  Siderial rotation
//    this->R *= RADSCALE;
//    glScaled(R,R,R);
//    drawSphere(this->tex);
//    glPopMatrix();
}
