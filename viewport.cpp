#include "viewport.h"
#include <iostream>
#include "mtrand.h"
#include "helperFunctions.h"

float inc = 0.001;
int elapsed = 0;
float t = 0;

unsigned short int DIM = 10;
//int psX, psY = 0;

float s1R = 4e10; float s1M = 2e30;
float s1_pos[] = { 8.33e10, 0, 0 };
float s1_vel[] = { 0, 0, 8.3e7 };

float s2R = 20e8; float s2M = 3e26;
float s2_pos[] = { 0, 7.25e10, 0 };
float s2_vel[] = { 9.4e7, 0, 0 };

float s3R = 8.1e7; float s3M = 3e30;
float s3_pos[] = { -7e10, 3e8, 0 };
float s3_vel[] = { 2e4, 7e7, -4e7 };

Star* s1 = new Star(s1_pos, s1_vel, s1R, s1M);
Star* s2 = new Star(s2_pos, s2_vel, s2R, s2M);
Star* s3 = new Star(s3_pos, s3_vel, s3R, s3M);

float nucleus_pos[] = { 0, 0, 0 };
float nucleusR = 6.7e9; float nucleusM = 8.2e36;

float intrude_pos[] = { 4e11, 3e5, 0 };
float intrude_vel[] = { -2e4, -3e4, -2e7 };
float intrudeR = 4.6e9; float intrudeM = 1.3e36;

BlackHole* nucleus = new BlackHole(nucleus_pos, nucleusR, nucleusM);
BlackHole* intrude = new BlackHole(intrude_pos, intrude_vel, intrudeR, intrudeM);

const unsigned short int nPoints = 10000;
float pointsX[nPoints]; float pointsY[nPoints]; float pointsZ[nPoints];

const unsigned short int nCloudPs = 10000;
float cpX[nCloudPs]; float cpY[nCloudPs]; float cpZ[nCloudPs];

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = ph = 15;
    asp = 1;           //  Aspect ratio
    fov = 80;
    mouse = 0;         //  Mouse movement
    dim = 10;
    merging = false;
    cubes = true;
    rideS = false;
    DIM = dim;

    animationTimer.setSingleShot(false);
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer.start(25);
}

void ViewPort::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    setMouseTracking(true);
    genTex();

    MTRand r(123);
    double R = nucleus->R + 5e10;
    for (unsigned short int i = 0; i < nPoints; ++i)
    {
        double theta = 2*M_PI*r();
        double radius = R*r();
        pointsX[i] = radius*cos(theta);
        pointsZ[i] = radius*sin(theta);
        pointsY[i] = -nucleus->R/4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nucleus->R/4+nucleus->R/4)));
    }

    for (unsigned short int i = 0; i < nCloudPs; ++i)
    {
        cpX[i] = -fov + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*fov)));
        cpY[i] = -fov + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*fov)));
        cpZ[i] = -fov + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2*fov)));
    }
}

void ViewPort::resizeGL(int width, int height)
{
    asp = (width && height) ? width / (float)height : 1;
    // Not to be confused with this class
    glViewport(0,0,width,height);
    project();
}

void ViewPort::project()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,asp,dim/8,8*dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateGL();
}

void ViewPort::animate()
{
    elapsed += qobject_cast<QTimer*>(sender())->interval();
    t = inc*elapsed;
    updateGL();
}

void ViewPort::reset(void)
{
    th = ph = 15; fov = 80;
    t = 0; elapsed = 0;
    merging = false;
    rideS = false;

    s1->x = s1_pos[0]; s1->y = s1_pos[1]; s1->z = s1_pos[2];
    s2->x = s2_pos[0]; s2->y = s2_pos[1]; s2->z = s2_pos[2];
    s3->x = s3_pos[0]; s3->y = s3_pos[1]; s3->z = s3_pos[2];

    s1->vx = s1_vel[0]; s1->vy = s1_vel[1]; s1->vz = s1_vel[2];
    s2->vx = s2_vel[0]; s2->vy = s2_vel[1]; s2->vz = s2_vel[2];
    s3->vx = s3_vel[0]; s3->vy = s3_vel[1]; s3->vz = s3_vel[2];

    nucleus->x = nucleus_pos[0]; nucleus->y = nucleus_pos[1]; nucleus->z = nucleus_pos[2];
    intrude->x = intrude_pos[0]; intrude->y = intrude_pos[1]; intrude->z = intrude_pos[2];

    nucleus->vx = nucleus->vy = nucleus->vz = 0;
    intrude->vx = intrude_vel[0]; intrude->vy = intrude_vel[1]; intrude->vz = intrude_vel[2];

    updateGL();
}

void ViewPort::ride() { rideS = !rideS; }

void ViewPort::beginMerge()
{
    t = 0; elapsed = 0;
    merging = true; cubes = false;
    t = 20;
    fov += 50;
    th = ph = 10;
    inc = 0.001;
    updateGL();
}

void ViewPort::toggleCubes() { cubes = !cubes; updateGL(); }

void ViewPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float Ex, Ey, Ez;
    Ex = -2*dim*Sin(th)*Cos(ph);
    Ey = +2*dim        *Sin(ph);
    Ez = +2*dim*Cos(th)*Cos(ph);
    if (merging && rideS)
    {
        float lx = pixel(nucleus->x, dim);
        float ly = pixel(nucleus->y, dim);
        float lz = pixel(nucleus->z, dim);
        Ex = pixel(intrude->x, dim);
        Ey = pixel(intrude->y, dim);
        Ez = pixel(intrude->z, dim);
        gluLookAt(Ex,Ey,Ez, lx,ly,lz, 0,Cos(ph),0);
    }
    else if (!merging && rideS)
    {
        Ex = pixel(s1->x, dim);
        Ey = pixel(s1->y, dim);
        Ez = pixel(s1->z, dim);
        gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0);
    }
    else { gluLookAt(Ex,Ey,Ez, 0,0,0, 0,Cos(ph),0); }

    for (unsigned char i = 0; i < nTex; ++i)
    { glBindTexture(GL_TEXTURE_2D, textures[i]); }

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    float black[]   = {0.0 , 0.0 , 0.0 , 1.0};
    float white[]   = {1.0 , 1.0 , 1.0 , 1.0};
    float red[]     = {0.5 , 0.2 , 0.2 , 1.0};
    float blue[]    = {0.0 , 0.7 , 1.0 , 1.0};

    glRotated(th,0,0,1);

    glEnable(GL_POINT_SPRITE);
    glBegin(GL_POINTS);
    for (unsigned short int i = 1; i < nCloudPs; ++i)
    {
        glColor4f(1,1,1,1);
        glNormal3f(-Ex, -Ey, -Ez);
        glVertex3f(cpX[i], cpY[i], cpZ[i]);
    }
    glEnd();
    glDisable(GL_POINT_SPRITE);

    if (merging)
    {
        float posIntrude[] = { intrude->x, intrude->y, intrude->z };
        float posNucleus[] = { nucleus->x, nucleus->y, nucleus->z };

        glEnable(GL_LIGHT0);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,white);
        glLightfv(GL_LIGHT0,GL_SPECULAR,black);
        glLightfv(GL_LIGHT0,GL_POSITION,posIntrude);

        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, black);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0, GL_SPECULAR, black);
        glLightfv(GL_LIGHT1, GL_POSITION, posNucleus);
    }

    else
    {
        float posS2[]   = {s2->x, s2->y, s2->z, 1.0};
        float posS1[]   = {s1->x, s1->y, s1->z, 1.0};
        float posS3[]   = {s3->x, s3->y, s3->z, 1.0};
        float origin[]  = {0,0,0,1};

        glEnable(GL_LIGHT0);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,blue);
        glLightfv(GL_LIGHT0,GL_SPECULAR,black);
        glLightfv(GL_LIGHT0,GL_POSITION,posS2);

        glEnable(GL_LIGHT1);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT1, GL_AMBIENT, black);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
        glLightfv(GL_LIGHT1, GL_SPECULAR, black);
        glLightfv(GL_LIGHT1, GL_POSITION, posS1);

        glEnable(GL_LIGHT2);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT2, GL_AMBIENT, black);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT2, GL_SPECULAR, black);
        glLightfv(GL_LIGHT2, GL_POSITION, origin);

        glEnable(GL_LIGHT3);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT2, GL_AMBIENT, black);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT2, GL_SPECULAR, black);
        glLightfv(GL_LIGHT2, GL_POSITION, posS3);
    }

    if(!merging)
    {
        glDisable(GL_LIGHTING);
        glEnable(GL_POINT_SPRITE);
        glBegin(GL_POINTS);
        for(unsigned short int i = 0; i < nPoints; i++)
        {
            glColor3f(1,1,1);
            glVertex3f(pixel(pointsX[i], dim), pixel(pointsY[i], dim), pixel(pointsZ[i], dim));
        }
        glEnd();
        glDisable(GL_POINT_SPRITE);
        glEnable(GL_LIGHTING);
    }

    if(cubes)
    {
        glColor3f(1,1,1);
        for(char i = 1; i <= 6; ++i)
        {
            glPushMatrix();
            glRotated(i*20, 1,1,1);
            cube(10*pow(-1,i),6/i,10*pow(-1,i), 0.5,0.5,0.5, 0);
            glPopMatrix();
        }
    }

    if(merging)
    {
        nucleus->draw(t, intrude, merging, dim);
        intrude->draw(t, nucleus, merging, dim);
    }
    else
    {
        nucleus->draw(t, NULL, merging, dim);
        s1->paint(t, nucleus, dim, textures[0]);
        s2->paint(t, nucleus, dim, textures[1]);
        s3->paint(t, nucleus, dim, textures[2]);
    }

    glFlush();
}

void ViewPort::mousePressEvent(QMouseEvent* e)
{
    mouse = true; pos = e->pos();
}

void ViewPort::mouseReleaseEvent(QMouseEvent *e)
{ mouse = false; }

void ViewPort::mouseMoveEvent(QMouseEvent* e)
{
    if (mouse)
    {
        QPoint d = e->pos()-pos;  //  Change in mouse location
        th = (th+d.x())%360;      //  Translate x movement to azimuth
        ph = (ph+d.y())%360;      //  Translate y movement to elevation
        pos = e->pos();           //  Remember new location
        updateGL();               //  Request redisplay
    }
}

void ViewPort::wheelEvent(QWheelEvent* e)
{
    // Zoom out
    if (e->delta()<0) { fov-=1; }
    // Zoom in
    else { fov+=1; }
    if(fov < 0) { fov = 0; }
    project();
}

void ViewPort::genTex()
{
    for (unsigned char j=0; j < nTex; ++j)
    {
        textures[j] = bindTexture
                (QPixmap(QString(":textures/tex%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }
}
