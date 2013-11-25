#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>
#include <QGLWidget>
#include <QString>
#include <QWidget>
#include <QtOpenGL>
#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

// Gravatational constant
const float G = 6.67e-11;
// World size
const float wmin = -5e10;
const float wmax = -wmin;

#endif // HELPERS_H
