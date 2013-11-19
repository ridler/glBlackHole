#include "viewport.h"
#include <OpenGL/glu.h>

float inc = 0.001;
int elapsed = 0;
float t = 0;

unsigned short int DIM = 0;
int psX, psY = 0;

float density = 0.25;
float fogColor[4] = {0.5, 0.5, 0.5, 1.0};

Star* s1 = new Star(8.33e10, 0, 0, 0, 0, 8.3e7, 37e8, 2e30, 0);
BlackHole* nucleus = new BlackHole(0,0,0,6.7e9,8.2e36);
//ParticleSystem* ps1 = new ParticleSystem(10, psX, psY, 7, DIM);

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = ph = 30;      //  Set intial display angles
    asp = 1;           //  Aspect ratio
    fov = 100;
    mouse = 0;         //  Mouse movement
    dim = 10;

    DIM = dim;

    animationTimer.setSingleShot(false);
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer.start(25);
}

void ViewPort::initializeGL()
{
    glEnable(GL_DEPTH_TEST); //  Enable Z-buffer depth testing
    setMouseTracking(true);  //  Ask for mouse events
}

void ViewPort::resizeGL(int width, int height)
{
    //  Window aspect ration
    asp = (width && height) ? width / (float)height : 1;
    //  Viewport is whole screen
    glViewport(0,0,width,height);
    //  Set projection
    project();
}

void ViewPort::project()
{
    //  Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    //  Undo previous transformations
    glLoadIdentity();
    //  Perspective transformation
    if (fov) { gluPerspective(fov,asp,dim/8,8*dim); }
    //  Orthogonal transformation
    else { glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim); }
    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
    updateGL();
}

void ViewPort::animate()
{
    elapsed += qobject_cast<QTimer*>(sender())->interval();
    t = inc*elapsed;
    update();
}

void ViewPort::paintGL()
{
//    glClearColor (0,0,0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float Ex = -2*dim*Sin(th)*Cos(ph);
    float Ey = +2*dim        *Sin(ph);
    float Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

    glEnable(GL_LIGHTING);

//    glEnable(GL_FOG);
//    glFogi (GL_FOG_MODE, GL_LINEAR);
//    glFogfv (GL_FOG_COLOR, fogColor);
//    glFogf (GL_FOG_DENSITY, density);
//    glHint (GL_FOG_HINT, GL_NICEST);
//    glFogf(GL_FOG_START, 1.0);
//    glFogf(GL_FOG_END, 5.0);

    float black[]   = {0.0 , 0.0 , 0.0 , 1.0};
    float white[]   = {1.0 , 1.0 , 1.0 , 1.0};
    float red[]     = {0.5 , 0.2 , 0.2 , 1.0};
    float pos[]     = {0.0 , 0.0 , 0.0 , 1.0};
    float posS1[]  = {s1->x  , s1->y  , s1->z  , 1.0};

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,black);
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0,GL_SPECULAR, black);
    glLightfv(GL_LIGHT1, GL_POSITION, posS1);

//    float solPos[] = {2,2,2};
//    float solMot[] = {0.41,-3.1,0.0};
//    float solKep[] = {0.022770,1.753555,0.273978,5.2026,0.0014503019,0.0484646,5.629731};
//    Star* sol = new Star(solPos, 8000000, 70000, solKep, solMot, 0);

//    float lunPos[] = {1.5,1.5,1.5};
//    float lunMot[] = {0.52,0.3,0.1};
//    float lunKep[] = {0.18770,0.923555,0.573978,4.8026,0.00214503019,0.00484646,3.829731};

    glRotated(th,0,0,1);

    nucleus->draw(dim);
    //sol->paint(t);
    s1->paint(t, nucleus, dim);
    //ps1->update(t, nucleus, dim);

    glFlush();
}

void ViewPort::mousePressEvent(QMouseEvent* e)
{
    mouse = true; pos = e->pos();
    psX = pos.x(); psY = pos.y();
}

void ViewPort::mouseReleaseEvent(QMouseEvent* e)
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
    //  Zoom out
    if (e->delta()<0) { fov-=1; }
    else { fov+=1; }
    if(fov < 0) { fov = 0; }
    project();
    //  Signal to change dimension spinbox
    emit dimen(dim);
}
