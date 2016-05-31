#include "mainwindow.h"
#include <QApplication>
#include <crectangle.h>
#include <QDebug>
#include "ctriangle.h"
#include "cregulapolygon.h"
#include <QJsonDocument>
#include <QFile>

void saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CRectangle rect(vec2(0,0), 5, 5, "name");
    CTriangle tria(glm::vec2(0,0), vec2(0,1), vec2(1,0), "triangle");
    CRegulaPolygon pol(4, 4, "rect");
    //CPolygon

    //qDebug() << round(rect[0].x*10)/10 << round(rect[0].y*10)/10;

    QJsonDocument doc;
    doc.setObject(tria.toJSON());
    qDebug() << pol.getRadius();
    std::shared_ptr<CTriangle> tri= CTriangle::load(doc.object());
    qDebug() << tri->perimeter() << tria.perimeter();

    //saveJson(doc, "rect.json");
    return 0;
}
