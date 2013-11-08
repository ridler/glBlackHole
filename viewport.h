#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "helpers.h"
#include "blackhole.h"
#include "star.h"

class ViewPort : public QGLWidget
{
Q_OBJECT                                             //  Qt magic macro
private:
   int    th,ph;     //  Display angles
   bool   mouse;     //  Mouse pressed
   QPoint pos;       //  Mouse position
   char dim;       //  Display size
   double asp;       //  Sceen aspect ratio
   double fov;
   void project();                        //  Set projection
   QTimer animationTimer;

public:
   ViewPort(QWidget* parent=0);                        //  Constructor
   QSize sizeHint() const {return QSize(400,400);}   //  Default size of widget

public slots:
//    void setDIM(double DIM);    //  Slot to set dim
    // void reset(void);           //  Reset view angles
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
