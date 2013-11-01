#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpers.h"
#include "viewport.h"

class MainWindow : public QWidget
{
Q_OBJECT                 //  Qt magic macro
private:
//   QDoubleSpinBox* s;    //  Spinbox for s
//   QDoubleSpinBox* b;    //  Spinbox for b
//   QDoubleSpinBox* r;    //  Spinbox for r
//   QDoubleSpinBox* dt;   //  Spinbox for dt
//   QDoubleSpinBox* dim;  //  Spinbox for dim
public:
   MainWindow(QWidget* parent=0); //  Constructor
private slots:
   // void setPAR(const QString&); //  Slot to set s,b,r,dt,dim
};

#endif // MAINWINDOW_H
