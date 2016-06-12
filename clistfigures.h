#ifndef CLISTFIGURES_H
#define CLISTFIGURES_H

#include "ccomplexfigure.h"
#include "cfigureparser.h"
#include "QTableWidget"

class CListFigures: public CComplexFigure
{
public:
    CListFigures();

    //void deleteFigure(const string& nameFigure);

    QTableWidget getTable(uint index);

};

#endif // CLISTFIGURES_H
