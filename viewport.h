#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "helpers.h"
#include "blackhole.h"
#include "star.h"
#include "particlesystem.h"
#include <QGLWidget>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

class ViewPort : public QGLWidget
{
    Q_OBJECT
private:
    int    th,ph;     //  Display angles
    bool   mouse;     //  Mouse pressed
    QPoint pos;       //  Mouse position
    double asp;       //  Sceen aspect ratio
    double fov;       //  field of view
    bool merging;     //  switches modes
    unsigned int textures[2];
    void genTex();
    void project();
    QTimer animationTimer;

public:
    unsigned short int dim;
    ViewPort(QWidget* parent=0);
    QSize sizeHint() const {return QSize(800,600);}

public slots:
    void reset(void);           // Reset view
    void beginMerge(void);      // Switch modes
private slots:
    void animate();

signals:
    void angles(QString text);  //  Signal for display angles
    void dimen(double dim);     //  Signal for display dimensions

protected:
    void initializeGL();                     //  Initialize widget
    void resizeGL(int width, int height);    //  Resize widget
    void paintGL();                          //  Draw widget
    void mousePressEvent(QMouseEvent* e);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent* e);  //  Mouse released
    void mouseMoveEvent(QMouseEvent* e);     //  Mouse moved
    void wheelEvent(QWheelEvent* e);         //  Mouse wheel
};

#endif // VIEWPORT_H
