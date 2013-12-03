#include "viewport.h"
#include <iostream>
#include "mtrand.h"

float inc = 0.001;
int elapsed = 0;
float t = 0;

unsigned short int DIM = 10;
int psX, psY = 0;

float density = 0.25;
float fogColor[4] = {0.5, 0.5, 0.5, 1.0};

// main mode objects
Star* s1 = new Star(8.33e10, 0, 0, 0, 0, 8.3e7, 37e8, 2e30);
Star* s2 = new Star(0, 7.25e10, 0, 9.4e7, 0, 0, 20e8, 3e26);
BlackHole* nucleus = new BlackHole(0,0,0,6.7e9,8.2e36);
//ParticleSystem* ps1 = new ParticleSystem(300, 0, 3e5, 5e10);

// merge mode objects
BlackHole* bh1 = new BlackHole(-4.8e10, 2.5e9, 2e5, 2e4, 0, 0, 3.2e9, 4.3e29);
BlackHole* bh2 = new BlackHole(2.2e11, -2.3e7, -5e9, -2e4, 0, 0, 5.6e9, 3.7e23);

const unsigned short int nPoints = 10000;
float pointsVx[100]; float pointsVy[100]; float pointsVz[100];
float pointsX[nPoints]; float pointsY[nPoints]; float pointsZ[nPoints];

static float pixel(float wx, unsigned short int dim)
{
    int pmin = -dim; int pmax = dim;
    float ratio = (pmax - pmin)/(wmax - wmin);
    float result = (wx - wmin)*ratio + pmin;
    return result;
}

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = ph = 0;      //  Set intial display angles
    asp = 1;           //  Aspect ratio
    fov = 100;
    mouse = 0;         //  Mouse movement
    dim = 10;
    merging = false;
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
    double R = nucleus->R + 2.6e10;
    for (unsigned short int i = 0; i < nPoints; ++i)
    {
        double theta = 2*M_PI*r();
        double radius = R*r();
        pointsX[i] = radius*cos(theta);
        pointsZ[i] = radius*sin(theta);
        pointsY[i] = -nucleus->R/4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nucleus->R/4+nucleus->R/4)));
        //cout << x << " " << y << endl;
    }

//    for(unsigned char i = 0; i < 100; i++)
//    {
//        pointsX[i] = cos(-nucleus->R) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(cos(nucleus->R+8e10)+cos(nucleus->R))));
//        pointsY[i] = -nucleus->R/4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nucleus->R/4+nucleus->R/4)));
//        pointsZ[i] = cos(-nucleus->R) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(cos(nucleus->R+8e10)+cos(nucleus->R))));
//    }
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
    th = ph = 0;
    t = 0; elapsed = 0;
    merging = false;
    fov -= 25;
    updateGL();
}

void ViewPort::beginMerge()
{
    merging = true; fov += 25; updateGL();
}

void ViewPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float Ex = -2*dim*Sin(th)*Cos(ph);
    float Ey = +2*dim        *Sin(ph);
    float Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

    for (unsigned char i = 0; i < 2; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures[i]); }

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    //    glEnable(GL_FOG);
    //    glFogi (GL_FOG_MODE, GL_LINEAR);
    //    glFogfv (GL_FOG_COLOR, fogColor);
    //    glFogf (GL_FOG_DENSITY, density);
    //    glHint (GL_FOG_HINT, GL_NICEST);
    //    glFogf(GL_FOG_START, 1.0);
    //    glFogf(GL_FOG_END, 5.0);

    float black[]   = {0.0 , 0.0 , 0.0 , 1.0};
    float white[]   = {1.0 , 1.0 , 1.0 , 1.0};
    // float red[]     = {0.5 , 0.2 , 0.2 , 1.0};

    glRotated(th,0,0,1);

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

        glEnable(GL_LIGHT0);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,white);
        glLightfv(GL_LIGHT0,GL_SPECULAR,black);
        glLightfv(GL_LIGHT0,GL_POSITION,posS2);

        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, black);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0,GL_SPECULAR, black);
        glLightfv(GL_LIGHT1, GL_POSITION, posS1);

        //    float solPos[] = {2,2,2};
        //    float solMot[] = {0.41,-3.1,0.0};
        //    float solKep[] = {0.022770,1.753555,0.273978,5.2026,0.0014503019,0.0484646,5.629731};

        //    float lunPos[] = {1.5,1.5,1.5};
        //    float lunMot[] = {0.52,0.3,0.1};
        //    float lunKep[] = {0.18770,0.923555,0.573978,4.8026,0.00214503019,0.00484646,3.829731};

        //        float pointsVx[100]; float pointsVy[100]; float pointsVz[100];
        //        float pointsX[100]; float pointsY[100]; float pointsZ[100];
        //        for(unsigned char i = 0; i < 100; i++)
        //        {
        //            pointsVx[i] = -2.99e8 + (float)rand()/((float)2.99e8);
        //            pointsVy[i] = -2.99e8 + (float)rand()/((float)2.99e8);
        //            pointsVz[i] = -2.99e8 + (float)rand()/((float)2.99e8);
        //        }

        glDisable(GL_LIGHTING);
        glEnable(GL_POINT_SPRITE);
        glBegin(GL_POINTS);
        for(unsigned short int i = 1; i <= nPoints; i++)
        {
            //            double denom = pow(pointsX[i]*pointsX[i] + pointsY[i]*pointsY[i] + pointsZ[i]*pointsZ[i], 1.5);
            //            double ax = -G*nucleus->mass*(pointsX[i])/denom;
            //            double ay = -G*nucleus->mass*(pointsY[i])/denom;
            //            double az = -G*nucleus->mass*(pointsZ[i])/denom;

            //            pointsVx[i] += ax*t;
            //            pointsVy[i] += ay*t;
            //            pointsVz[i] += az*t;

            //            pointsX[i] += pointsVx[i]*t;
            //            pointsY[i] += pointsVy[i]*t;
            //            pointsZ[i] += pointsVz[i]*t;

            //            std::cout << pixel(pointsX[i], dim) << "\n";
            //            glVertex3f(pixel(pointsX[i], dim), 0, 0);
            float zh = fmod(90*t,360.0);
            float Position[]  = {pointsX[i]*cos(zh),0,pointsZ[i]*sin(zh)};
            glColor3f(1,1,1);
            pointsX[i] = Position[0];
            pointsZ[i] = Position[2];
            glVertex3f(pixel(pointsX[i], dim), pixel(pointsY[i], dim), pixel(pointsZ[i], dim));
        }
        glEnd();
        glEnable(GL_LIGHTING);

        nucleus->draw(t, NULL, merging, dim);
        s1->paint(t, nucleus, dim, textures[0]);
        s2->paint(t, nucleus, dim, 0);
        //ps1->update(t, nucleus, dim);
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
    for (unsigned char j=0; j < 2; ++j)
    {
        textures[j] = bindTexture
                (QPixmap(QString(":textures/tex%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }
}
