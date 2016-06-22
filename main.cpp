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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<CPolygon> rect( new CRectangle(vec2(0,0), 5, 5, "name"));
    std::shared_ptr<CPolygon> tria( new CTriangle(glm::vec2(0,0), vec2(0,1), vec2(1,0), "triangle"));
    std::shared_ptr<CPolygon> pl ( new CRegulaPolygon(vec2(0,0), 45, sqrt(2), 4, "regPol"));

    CComplexFigure list("list");

    list.addFigure(std::shared_ptr<CFigure>(new CPyramid(5, pl, "piramid")));
    list.addFigure(std::shared_ptr<CFigure>(new CPrism(rect, 5, "RectPrism")));
    list.addFigure(std::shared_ptr<CFigure>(new CPrism(tria, 5, "prism1")));
    list.addFigure(std::shared_ptr<CFigure>(new CPrism(pl, 5, "prism3")));
    list.addFigure(std::shared_ptr<CFigure>(new CDodecahedron(2, "dod")));

    CFigureParser parser("file.json");
    parser.save(list.toJSON());

    MainWindow m;
    m.show();


    return a.exec();
}



