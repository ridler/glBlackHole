#include "star.h"

Star::Star(float x, float y, float z, float mass, float R, unsigned int tex)
{
    this->x = x; this->y = y; this->z = z;
    this->mass = mass; this->R = R; this->tex = tex;
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

void Star::draw()
{
   int th,ph;
   glTranslated(this->x, this->y, this->z);
   glScaled(this->R, this->R, this->R);
   //  Set texture
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,this->tex);
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
