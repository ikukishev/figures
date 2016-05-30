#ifndef CREGULAPOLYGON_H
#define CREGULAPOLYGON_H

#include "cpolygon.h"


#define PI 3.14159265

class CRegulaPolygon: public CPolygon
{
public:
    CRegulaPolygon();
    CRegulaPolygon(double radius, int countAngles, const string& name);

    // CPolygon interface
    double area() const ;
    double perimeter() const;

};

#endif // CREGULAPOLYGON_H
