#ifndef CREGULAPOLYGON_H
#define CREGULAPOLYGON_H

#include "cpolygon.h"

class CRegulaPolygon: public CPolygon
{
   DECLARE_FIGURE
private:
   CRegulaPolygon();
public:

    CRegulaPolygon(const vec2& centerPoint, double startAngle, double radius, int countAngles, const string& name);

    static std::shared_ptr<CRegulaPolygon> load(const QJsonObject& object);
    virtual QJsonObject toJSON() const;

    double getRadius() const;
    virtual double area() const ;
    virtual double perimeter() const;
    vec2 getCenter() {return mCenter;}

private:
    vec2 mCenter;
    double mStartAngle;
};

#endif // CREGULAPOLYGON_H
