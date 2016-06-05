#include "mainwindow.h"
#include <QApplication>
#include "crectangle.h"
#include "ctriangle.h"
#include "cregulapolygon.h"
#include "cpyramid.h"
#include "cprism.h"
#include "cdodecahedron.h"
#include <QJsonDocument>
#include <QFile>
#include <iostream>


using std::cout;

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

    CRegulaPolygon regPol(vec2(0,0), 45, sqrt(2), 4, "regPol");
    QJsonDocument doc;
    doc.setObject(regPol.toJSON());

    //std::shared_ptr<CPolygon> pl = regPol.load(doc.object());

//    CPyramid cp(5, pl, "piramid");
//    CPrism prism(pl, 5, "prism");

//    QJsonDocument doc1;
//    doc1.setObject(cp.toJSON());

//    CRegulaPolygon reg(vec2(0,0), 0, 1, 5, "reg");
//    CDodecahedron dod(5, "dod");
//    //glm::rotate()
//    std::cout<< " " << dod.volume() << " "<< dod.getLenght();

//    saveJson(doc1, "prism.json");



    return 0;
}



