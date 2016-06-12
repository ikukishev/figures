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
//    prism.setHeight(10);
    QJsonDocument doc1;
    doc1.setObject(cp.toJSON());

//    CRegulaPolygon reg(vec2(0,0), 0, 1, 5, "reg");
    CDodecahedron dod(5, "dod");
//    //glm::rotate()

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

//    QJsonDocument document;
//    std::shared_ptr<CFigure> fig = parser.getObject(dod.toJSON());
//    document.setObject(fig->toJSON());
//    saveJson(document, "testParser.json");

    MainWindow m;
    m.show();
//    QStringList listHeaders;

//    listHeaders.insert(0, "name");
//    listHeaders.insert(1, "type");
//    listHeaders.insert(2, "edges");
//    listHeaders.insert(3, "facets");
//    listHeaders.insert(4, "vertex");
//    listHeaders.insert(5, "volume");
//    listHeaders.insert(6, "surface area");

//    QTableWidget table;

//    table.setRowCount(3);
//    table.setRowHeight(0, 20);

//    table.setColumnCount(7);
//    table.setColumnWidth(0,50);

//    table.setHorizontalHeaderLabels(listHeaders);

//    QTableWidgetItem item[3][7];


//    for(int i(0); i<3; i++)
//    {
//        item[i][0].setText(QString::fromStdString(list(i)->getName()));
//        item[i][1].setText(QString::fromStdString(list(i)->type()));
//        item[i][2].setText(QString::number(list(i)->countEdge()));
//        item[i][3].setText(QString::number(list(i)->countFacets()));
//        item[i][4].setText(QString::number(list(i)->countVertex()));
//        item[i][5].setText(QString::number(list(i)->volume()));
//        item[i][6].setText(QString::number(list(i)->surfaceArea()));
//    }

//    for(int i(0); i<3; i++){
//        for(int j(0); j<7; j++)
//        {
//            item[i][j].setTextAlignment(Qt::AlignCenter);
//            table.setItem(i,j,&item[i][j]);
//        }
//    }
//    table.show();

    return a.exec();
}



