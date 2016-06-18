#include "mainwindow.h"
#include <QApplication>
#include "crectangle.h"
#include "ctriangle.h"
#include "cregulapolygon.h"
#include "cpyramid.h"
#include "cprism.h"
#include "cdodecahedron.h"
#include <QJsonDocument>
#include "ccomplexfigure.h"
#include <QFile>
#include <QLabel>
#include <iostream>
#include <cfigureparser.h>
#include <QTableWidget>

using std::cout;

void saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

string jsonToString(const QJsonObject& obj)
{
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toBinaryData().toStdString();
}

QJsonDocument loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CRectangle rect(vec2(0,0), 5, 5, "name");
    CTriangle tria(glm::vec2(0,0), vec2(0,1), vec2(1,0), "triangle");

    CFigureParser parserrr("triangle.json");
    parserrr.save(tria.toJSON());

    CRegulaPolygon regPol(vec2(0,0), 45, sqrt(2), 4, "regPol");
    QJsonDocument doc;
    doc.setObject(regPol.toJSON());

    std::shared_ptr<CPolygon> pl = regPol.load(doc.object());

    CPyramid cp(5, pl, "piramid");
    CPrism prism(pl, 5, "prism");
    CPrism prism1(pl, 5, "prism1");
    CPrism prism2(pl, 5, "prism2");
    CPrism prism3(pl, 5, "prism3");
    CPrism prism4(pl, 5, "prism4");

    QJsonDocument doc1;
    doc1.setObject(cp.toJSON());

    CDodecahedron dod(5, "dod");

    CComplexFigure list("list");

    list.addFigure(prism.load(prism.toJSON()));
    list.addFigure(prism1.load(prism1.toJSON()));
    list.addFigure(prism2.load(prism2.toJSON()));
    list.addFigure(prism3.load(prism3.toJSON()));
    list.addFigure(prism4.load(prism4.toJSON()));

    list.addFigure(cp.load(cp.toJSON()));
    list.addFigure(dod.load(dod.toJSON()));

    CFigureParser parser("file.json");
    parser.save(list.toJSON());

    MainWindow m;
    m.show();


    return a.exec();
}



