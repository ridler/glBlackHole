#include "viewport.h"
#include <OpenGL/glu.h>

float inc = 0.1;
int elapsed = 0;
float t = 0;

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = ph = 30;      //  Set intial display angles
    asp = 1;           //  Aspect ratio
    dim = 10;          //  World dimension
    fov = 0;
    mouse = 0;         //  Mouse movement

    animationTimer.setSingleShot(false);
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer.start(25);
}

void ViewPort::setDIM(double DIM)
{
    dim = DIM;    //  Set parameter
    project();
    updateGL();   //  Request redisplay
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
    if (fov)
       gluPerspective(fov,asp,dim/16,16*dim);
    //  Orthogonal transformation
    else
       glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
}

void ViewPort::animate()
{
    elapsed += qobject_cast<QTimer*>(sender())->interval();
    t = elapsed;
    update();
}

void ViewPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float black[]   = {0.0 , 0.0 , 0.0 , 1.0};
    float white[]   = {1.0 , 1.0 , 1.0 , 1.0};
    float pos[]     = {0.0 , 0.0 , 0.0 , 1.0};
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_AMBIENT ,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,black);
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    glRotated(th,0,0,1);

    BlackHole* nucleus = new BlackHole(0,0,0,2.2,612983467023);
    nucleus->draw(t);

    float solPos[] = {2,2,2};
    float solMot[] = {0.41,-3.1,0.0};
    float solKep[] = {0.022770,1.753555,0.273978,5.2026,0.0014503019,0.0484646,5.629731};
    Star* sol = new Star(solPos, 8000000, 70000, solKep, solMot, 0);
    sol->paint(t);

    glFlush();
}

void ViewPort::mousePressEvent(QMouseEvent* e)
{ mouse = true; pos = e->pos(); }

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
    if (e->delta()<0)
    { setDIM(dim+1); fov-=0.01; }
    //  Zoom in
    else if (dim>2)
    { setDIM(dim-1); fov+=0.01; }
    //  Signal to change dimension spinbox
    emit dimen(dim);
}
