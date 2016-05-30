#ifndef CREGULAPOLYGON_H
#define CREGULAPOLYGON_H

#include "cpolygon.h"

class CRegulaPolygon: public CPolygon
{
private:
   CRegulaPolygon();
public:

    CRegulaPolygon(double radius, int countAngles, const string& name);

    // CPolygon interface
    virtual double area() const ;
    virtual double perimeter() const;

};

#endif // CREGULAPOLYGON_H
