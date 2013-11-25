#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "helpers.h"
#include "blackhole.h"
#include "star.h"
#include "particlesystem.h"

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

class ViewPort : public QGLWidget
{
    Q_OBJECT                                             //  Qt magic macro
private:
    int    th,ph;     //  Display angles
    bool   mouse;     //  Mouse pressed
    QPoint pos;       //  Mouse position
    double asp;       //  Sceen aspect ratio
    double fov;
    bool merging;
    void project();
    QTimer animationTimer;

public:
    unsigned short int dim;       //  Display size
    ViewPort(QWidget* parent=0);                        //  Constructor
    QSize sizeHint() const {return QSize(800,600);}   //  Default size of widget

public slots:
    //    void setDIM(double DIM);    //  Slot to set dim
    void reset(void);           //  Reset view angles
    void beginMerge(void);
private slots:
    void animate();

signals:
    void angles(QString text);  //  Signal for display angles
    void dimen(double dim);     //  Signal for display dimensions

protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    void mousePressEvent(QMouseEvent* e);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent* e);  //  Mouse released
    void mouseMoveEvent(QMouseEvent* e);     //  Mouse moved
    void wheelEvent(QWheelEvent* e);         //  Mouse wheel
};

#endif // VIEWPORT_H
