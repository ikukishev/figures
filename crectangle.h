#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "cpolygon.h"

class CRectangle: public CPolygon
{
private:
   CRectangle();
public:

    CRectangle(vec2 downLeftAngle, double length, double width, const string& name);

public:
    virtual double area() const;
    virtual double perimeter() const;
};

#endif // CRECTANGLE_H
