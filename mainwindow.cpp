#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   CPoint<int> d(2,2,2), d1(1, 1, 1);
   /*d=d+d1;
   d*=d1;*/
   d.scalingPoint1(d1, 2);
   ui->label->setNum(d.mX);
}

MainWindow::~MainWindow()
{
   delete ui;
}
