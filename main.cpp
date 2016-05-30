#include "mainwindow.h"
#include <QApplication>
#include <crectangle.h>
#include <QDebug>
#include "ctriangle.h"
#include "cregulapolygon.h"
#include <QJsonDocument>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CRectangle rect(vec2(0,0), 5, 5, "name");

    //CPolygon

    //qDebug() << round(rect[0].x*10)/10 << round(rect[0].y*10)/10;

    QJsonDocument doc;
    doc.setObject(rect.toJSON());
    qDebug() << doc.toJson();
    std::shared_ptr<CRectangle> rec= CRectangle::load(doc.object());
    qDebug() << rec->getLength() << 2323;

    return 0;
}
