#ifndef CREGULAPOLYGON_H
#define CREGULAPOLYGON_H

#include "cpolygon.h"

class CRegulaPolygon: public CPolygon
{
   DECLARE_FIGURE
private:
   CRegulaPolygon();
public:

    CRegulaPolygon(double radius, int countAngles, const string& name);

    // CPolygon interface
    static std::shared_ptr<CRegulaPolygon> load(const QJsonObject& object);
    virtual QJsonObject toJSON() const;

    double getRadius() const;
    virtual double area() const ;
    virtual double perimeter() const;

};

#endif // CREGULAPOLYGON_H
