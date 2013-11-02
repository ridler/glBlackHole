#include "star.h"

Star::Star(float pos[], float m, float R, float kep[], float mot[], unsigned int tex)
{
    this->x = pos[0]; this->y = pos[1]; this->z = pos[2];
    this->mass = mass; this->R = R; this->tex = tex;
    this->rot = mot[0]; this->th = rot[1]; this->ph = mot[2];
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
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}

void Star::updatePos(float t)
{
       //  Calculate true anomaly
       double M = fmod(day*n+l-p,TWOPI); //  Mean anomaly in radians
       double delta;
       double v = M;
       do
       {
          delta = v - e*sin(v) - M;
          v -= delta/(1-e*cos(v));
       } while (fabs(delta)>1e-12);
       //  True anomaly
       v = 2*atan(sqrt((1+e)/(1-e))*tan(0.5*v));
       double oR = a*(1-e*e)/(1+e*cos(v)); //  Orbit radius (AU)
       double h = v + p - o;              //  Elliptical angle
       //  Compute and apply location
       this->x = oR * (cos(o)*cos(h) - sin(o)*sin(h)*cos(i));
       this->y = oR * (sin(o)*cos(h) + cos(o)*sin(h)*cos(i));
       this->z = oR *                        (sin(h)*sin(i));
    }

    //  Transform and draw planet
    glPushMatrix();
    glRotated(planet[k].th,1,0,0);           //  Declination
    glRotated(360*day/planet[k].rot,0,0,1);  //  Siderial rotation
}

void Star::draw(float t)
{
   int th,ph;
   glTranslated(this->x, this->y, this->z);
   glScaled(this->R, this->R, this->R);
   //  Set texture
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,this->tex);
   glColor3f(1,0,0);
   //  Latitude bands
   glColor3f(1,1,1);
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
