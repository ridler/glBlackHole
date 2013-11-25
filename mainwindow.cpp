#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    :  QWidget(parent)
{
   setWindowTitle(tr("Black Hole Simulation"));

   ViewPort* galaxy = new ViewPort;

   QPushButton* reset = new QPushButton("Reset");
   QPushButton* merge = new QPushButton("Begin Merger");

   //  Connect signals to slots
   connect(reset, SIGNAL(clicked(void)), galaxy, SLOT(reset(void)));
   connect(merge, SIGNAL(clicked(void)), galaxy, SLOT(beginMerge(void)));

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(4,100);

   layout->addWidget(galaxy,0,0,5,1);

   //  Group Control parameters
   QGroupBox* dspbox = new QGroupBox("Controls");
   QGridLayout* dsplay = new QGridLayout;
   dsplay->addWidget(reset,2,1);
   dsplay->addWidget(merge,3,1);
   dspbox->setLayout(dsplay);
   layout->addWidget(dspbox,2,1);

   //  Overall layout
   setLayout(layout);
}
