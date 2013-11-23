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

const float G = 6.67e-11;
const float rScale = 2.9e-10;
const float pScale = 2e-10;
const float wmin = -5e10;
const float wmax = -wmin;

#endif // HELPERS_H
