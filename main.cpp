#include "mainwindow.h"
#include <QApplication>
#include <crectangle.h>
#include <QDebug>
#include "ctriangle.h"
#include "cregulapolygon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CRegulaPolygon rect(1, 3, "name");

    qDebug() << round(rect[0].x*10)/10 << round(rect[0].y*10)/10;

    qDebug() << rect.perimeter();

    return 0;
}
