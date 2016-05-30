#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "cpolygon.h"

class CRectangle: public CPolygon
{

   DECLARE_FIGURE
private:
   CRectangle();
public:
    CRectangle(vec2 downLeftAngle, double length, double width, const string& name);

    virtual QJsonObject toJSON() const;
    static std::shared_ptr<CRectangle> load(const QJsonObject& object);

    virtual double area() const;
    virtual double perimeter() const;

    double getWidth() const;
    double getLength() const;
    vec2 getDownLeftAngle() const;

    CRectangle& setWidth(double width);
    CRectangle& setLength( double length);
    CRectangle& setDownLeftAngle(vec2 point);

};

#endif // CRECTANGLE_H
