#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    :  QWidget(parent)
{
   //  Set window title
   setWindowTitle(tr("Black Hole Simulation"));

   //  Create new Lorenz widget
   ViewPort* galaxy = new ViewPort;

   //  Display widget for angles and dimension
   // QLabel* angles = new QLabel();
//   //  Pushbutton to reset view angle
//   QPushButton* reset = new QPushButton("Reset");

//   //  Combo box for preset s/b/r & dt & dim values
//   QComboBox* preset = new QComboBox;
//   preset->addItems(QStringList() << "Preset SBR, dt & dim"
//      << "A:10.0 ,  2.666 ,  28.0 , 0.001 ,  50"
//      << "B:10.0 ,  2.67  ,  15.0 , 0.001 ,  25"
//      << "C:10.0 ,  2.67  ,  12.0 , 0.001 ,  25"
//      << "D:10.0 ,  2.666 , 250.0 , 0.001 , 500"
//      << "E:17.0 ,  9.0   ,  16.5 , 0.03  ,  50"
//      << "F:10.0 ,  0.50  ,  20.0 , 0.001 ,  50"
//      << "G:-1.7 ,  2.66  ,  50.0 , 0.003 ,  75"
//      << "H:-1.0 ,  2.66  ,  50.0 , 0.003 ,  50"
//      << "I:-1.0 , 12.00  , 200.0 , 0.001 , 150"
//      << "J:-1.0 ,  0.067 ,   2.9 , 0.01  ,   2"
//      << "K:-3.0 ,  2.66  ,  50.0 , 0.003 , 500");

//   //  Connect valueChanged() signals to Lorenz slots
//   connect(s     , SIGNAL(valueChanged(double)) , lorenz , SLOT(setS(double)));
//   connect(b     , SIGNAL(valueChanged(double)) , lorenz , SLOT(setB(double)));
//   connect(r     , SIGNAL(valueChanged(double)) , lorenz , SLOT(setR(double)));
//   connect(x0    , SIGNAL(valueChanged(double)) , lorenz , SLOT(setX0(double)));
//   connect(y0    , SIGNAL(valueChanged(double)) , lorenz , SLOT(setY0(double)));
//   connect(z0    , SIGNAL(valueChanged(double)) , lorenz , SLOT(setZ0(double)));
//   connect(dt    , SIGNAL(valueChanged(double)) , lorenz , SLOT(setDT(double)));
//   connect(dim   , SIGNAL(valueChanged(double)) , lorenz , SLOT(setDIM(double)));
//   connect(reset , SIGNAL(clicked(void))        , lorenz , SLOT(reset(void)));
//   //  Connect lorenz signals to display widgets
//   connect(lorenz , SIGNAL(angles(QString)) , angles , SLOT(setText(QString)));
//   connect(lorenz , SIGNAL(dimen(double))   , dim    , SLOT(setValue(double)));
//   //  Connect combo box to setPAR in myself
//   connect(preset , SIGNAL(currentIndexChanged(const QString&)), this , SLOT(setPAR(const QString&)));

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(4,100);

   //  Lorenz widget
   layout->addWidget(galaxy,0,0,5,1);

//   //  Group SBR parameters
//   QGroupBox* sbrbox = new QGroupBox("Lorenz Parameters");
//   QGridLayout* sbrlay = new QGridLayout;
//   sbrlay->addWidget(new QLabel("s (Prandtl)"),0,0);   sbrlay->addWidget(s,0,1);
//   sbrlay->addWidget(new QLabel("b (Beta)"),1,0);      sbrlay->addWidget(b,1,1);
//   sbrlay->addWidget(new QLabel("r (Rayleigh)"),2,0);  sbrlay->addWidget(r,2,1);
//   sbrbox->setLayout(sbrlay);
//   layout->addWidget(sbrbox,0,1);

//   //  Group Origin parameters
//   QGroupBox* xyzbox = new QGroupBox("Origin");
//   QGridLayout* xyzlay = new QGridLayout;
//   xyzlay->addWidget(new QLabel("x0"),0,0);  xyzlay->addWidget(x0,0,1);
//   xyzlay->addWidget(new QLabel("y0"),1,0);  xyzlay->addWidget(y0,1,1);
//   xyzlay->addWidget(new QLabel("z0"),2,0);  xyzlay->addWidget(z0,2,1);
//   xyzbox->setLayout(xyzlay);
//   layout->addWidget(xyzbox,1,1);

//   //  Group Display parameters
//   QGroupBox* dspbox = new QGroupBox("Display");
//   QGridLayout* dsplay = new QGridLayout;
//   dsplay->addWidget(new QLabel("dt"),0,0);  dsplay->addWidget(dt,0,1);
//   dsplay->addWidget(new QLabel("dim"),1,0); dsplay->addWidget(dim,1,1);
//   dsplay->addWidget(angles,2,0);            dsplay->addWidget(reset,2,1);
//   dspbox->setLayout(dsplay);
//   layout->addWidget(dspbox,2,1);

//   //  Preset Values
//   layout->addWidget(preset,3,1);

   //  Overall layout
   setLayout(layout);
}

//
//  Set SBR, dt & dim in viewer
//
//void Viewer::setPAR(const QString& str)
//{
//   QStringList par = str.mid(2).split(',');
//   if (par.size()<5) return;
//   s->setValue(par[0].toDouble());
//   b->setValue(par[1].toDouble());
//   r->setValue(par[2].toDouble());
//   dt->setValue(par[3].toDouble());
//   dim->setValue(par[4].toDouble());
//}
