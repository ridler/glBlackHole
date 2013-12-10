#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
#include "helpers.h"

void billboardBegin()
{

    float modelview[16];
    int i,j;

    // save the current modelview matrix
    glPushMatrix();

    // get the current modelview matrix
    glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

    // undo all rotations
    // beware all scaling is lost as well
    for( i=0; i<3; i++ )
        for( j=0; j<3; j++ ) {
            if ( i==j )
                modelview[i*4+j] = 1.0;
            else
                modelview[i*4+j] = 0.0;
        }

    // set the modelview with no rotations
    glLoadMatrixf(modelview);
}

// converts "world" coordinates into screen coordinates
float pixel(float wx, unsigned short int dim)
{
    int pmin = -dim; int pmax = dim;
    float ratio = (pmax - pmin)/(wmax - wmin);
    float result = (wx - wmin)*ratio + pmin;
    return result;
}

// For Drawing Spheres
void Vertex(double th,double ph)
{
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z =         Sin(ph);
    glNormal3d(x,y,z);
    glTexCoord2d(th/360.0,ph/180.0+0.5);
    glVertex3d(x,y,z);
}

void sphere(float x, float y, float z, float r,
    unsigned int tex)
{
    const unsigned char d = 5;
    short t, p;

    glTranslated(x,y,z);
    glScaled(r,r,r);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        //  Latitude bands
    for (p=-90;p<90;p+=d)
    {
        glBegin(GL_QUAD_STRIP);
        for (t=0;t<=360;t+=d)
        {
            Vertex(t,p);
            Vertex(t,p+d);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void cube(float x, float y, float z,
    float dx, float dy, float dz, unsigned int tex)
{
    glPushMatrix();

    glTranslated(x,y,z);
    glScaled(dx,dy,dz);

    glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //	Front
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    glEnd();
   //	Back
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    glEnd();
   //  Right
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    glEnd();
   //  Left
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glEnd();
   //  Top
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
   //  Bottom
    glBegin(GL_QUADS);
    glNormal3f( 0,-1, 0);
    glVertex3f(-1,-1,-1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,-1,+1);
    glVertex3f(-1,-1,+1);
    glEnd();
   //  Undo transformations and textures
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
