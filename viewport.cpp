#include "viewport.h"

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
   th = ph = 30;      //  Set intial display angles
   asp = 1;           //  Aspect ratio
   dim = 10;          //  World dimension
   mouse = 0;         //  Mouse movement
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
    //  Orthogonal projection to dim
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (asp>1)
       glOrtho(-dim*asp, +dim*asp, -dim, +dim, -3*dim, +3*dim);
    else
       glOrtho(-dim, +dim, -dim/asp, +dim/asp, -3*dim, +3*dim);

    //  Back to model view
    glMatrixMode(GL_MODELVIEW);
}

void ViewPort::paintGL()
{
    // like glutDispaly()
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
       setDIM(dim+1);
    //  Zoom in
    else if (dim>2)
       setDIM(dim-1);
    //  Signal to change dimension spinbox
    emit dimen(dim);
}
