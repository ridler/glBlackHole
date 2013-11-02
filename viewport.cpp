#include "viewport.h"

unsigned char one       =   1;  // Unit value
unsigned char distance  =   5;  // Light distance
float inc                         =   1;  // Ball increment
unsigned char smooth    =   1;  // Smooth/Flat shading
short local                            =   0;  // Local Viewer Model
unsigned char emission  =   0;  // Emission intensity (%)
unsigned char ambient   =  30;  // Ambient intensity (%)
unsigned char diffuse   = 100;  // Diffuse intensity (%)
unsigned char specular  =   0;  // Specular intensity (%)
unsigned short shininess =  0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
short zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

int elapsed = 0;
float t = 0;

static inline void Vertex(double th,double ph)
{
        double x = Sin(th)*Cos(ph);
        double y = Cos(th)*Cos(ph);
        double z =         Sin(ph);
        glNormal3d(x,y,z);
        glVertex3d(x,y,z);
}

static void sphere(float x, float y, float z, float r)
{
        const unsigned char d = 5;
        float yellow[] = {1.0,1.0,0.0,1.0};
        float Emission[]  = {0.0,0.0,0.01*emission,1.0};
        short th,ph;
        glPushMatrix();
        {
                glTranslated(x,y,z);
                glScaled(r,r,r);
                glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
                glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
                glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

                   //  Latitude bands
                for (ph=-90;ph<90;ph+=d)
                {
                        glBegin(GL_QUAD_STRIP);
                        for (th=0;th<=360;th+=d)
                        {
                                Vertex(th,ph);
                                Vertex(th,ph+d);
                        }
                        glEnd();
                }
        }
        glPopMatrix();
}

ViewPort::ViewPort(QWidget* parent)
    : QGLWidget(parent)
{
    th = ph = 30;      //  Set intial display angles
    asp = 1;           //  Aspect ratio
    dim = 10;          //  World dimension
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

void ViewPort::animate()
{
    elapsed += qobject_cast<QTimer*>(sender())->interval();
    t = inc*elapsed/(1000.0);
    zh = fmod(90*t,360.0);
    update();
}

void ViewPort::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

    //  Translate intensity to color vectors
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //  Light position
    float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
    //  Draw light position as ball (still no lighting here)
    glColor3f(1,1,1);
    sphere(Position[0],Position[1],Position[2] , 0.1);
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);

    glRotated(th,0,0,1);

    BlackHole* nucleus = new BlackHole(0,0,0,2.2,612983467023);
    nucleus->draw();

    Star* sol = new Star(5,5,5,19834756, 1.3, 0);
    sol->draw(t);

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
        setDIM(dim+1);
    //  Zoom in
    else if (dim>2)
        setDIM(dim-1);
    //  Signal to change dimension spinbox
    emit dimen(dim);
}
