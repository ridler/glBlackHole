#include "viewport.h"
#include <iostream>
#include "mtrand.h"
#include "helperFunctions.h"

float inc = 0.001;
int elapsed = 0;
float t = 0;

unsigned short int DIM = 10;
int psX, psY = 0;

float density = 0.25;
float fogColor[4] = {0.5, 0.5, 0.5, 1.0};

// main mode objects
Star* s1 = new Star(8.33e10, 0, 0, 0, 0, 8.3e7, 4e10, 2e30);
Star* s2 = new Star(0, 7.25e10, 0, 9.4e7, 0, 0, 20e8, 3e26);
Star* s3 = new Star(-7e10,3e8,0, 2e6,3e5,9e7, 8.1e7, 3e30);
BlackHole* nucleus = new BlackHole(0,0,0,6.7e9,8.2e36);
//ParticleSystem* ps1 = new ParticleSystem(300, 0, 3e5, 5e10);

// merge mode objects
BlackHole* bh1 = new BlackHole(-4.8e10, 2.5e9, 2e5, 2e4, 0, 0, 3.2e9, 4.3e29);
BlackHole* bh2 = new BlackHole(2.2e11, -2.3e7, -5e9, -2e4, 0, 0, 5.6e9, 3.7e23);

const unsigned short int nPoints = 10000;
float pointsX[nPoints]; float pointsY[nPoints]; float pointsZ[nPoints];

const unsigned short int nCloudPs = 10000;
float cpX[nCloudPs]; float cpY[nCloudPs]; float cpZ[nCloudPs];

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = 0;
    ph = 10;      //  Set intial display angles
    asp = 1;           //  Aspect ratio
    fov = 80;
    mouse = 0;         //  Mouse movement
    dim = 10;
    merging = false;
    cubes = true;
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
        //cout << x << " " << y << endl;
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
    //  Viewport is whole screen
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
    th = ph = 15;
    t = 0; elapsed = 0;
    merging = false;
    fov -= 25;
    updateGL();
}

void ViewPort::beginMerge()
{
    merging = true; fov += 25;
    inc = 0.1; updateGL();
}

void ViewPort::toggleCubes() { cubes = !cubes; updateGL(); }

void ViewPort::slideInc()
{ return; }

void ViewPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float Ex = -2*dim*Sin(th)*Cos(ph);
    float Ey = +2*dim        *Sin(ph);
    float Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

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
        float posBH1[] = { bh1->x, bh1->y, bh1->z };
        float posBH2[] = { bh2->x, bh2->y, bh2->z };

        glEnable(GL_LIGHT0);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,white);
        glLightfv(GL_LIGHT0,GL_SPECULAR,black);
        glLightfv(GL_LIGHT0,GL_POSITION,posBH1);

        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, black);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0, GL_SPECULAR, black);
        glLightfv(GL_LIGHT1, GL_POSITION, posBH2);

        bh1->draw(t, bh2, merging, dim);
        bh2->draw(t, bh1, merging, dim);
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

        glDisable(GL_LIGHTING);
        glEnable(GL_POINT_SPRITE);
        glBegin(GL_POINTS);
        for(unsigned short int i = 1; i < nPoints; i++)
        {
            glColor3f(1,1,1);
            glVertex3f(pixel(pointsX[i], dim), pixel(pointsY[i], dim), pixel(pointsZ[i], dim));
        }
        glEnd();
        glDisable(GL_POINT_SPRITE);
        glEnable(GL_LIGHTING);

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
