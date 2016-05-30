#include "cregulapolygon.h"

CRegulaPolygon::CRegulaPolygon(double radius, int countAngles, const std::string &name)
    : CPolygon(countAngles, name)
{
    double ang=0, dAngle=360.0/countAngles;
    for(int i(0); i<countAngles; i++)
    {
        ang+=dAngle;
        (*this)[i].x=radius*cos(ang*PI/180.0);
        (*this)[i].y=radius*sin(ang*PI/180.0);
    }
}

double CRegulaPolygon::area() const
{
   double mLenghtEdge=distance((*this)[0], (*this)[1]);
   return countAngles()*mLenghtEdge*mLenghtEdge/(4*tan(180/countAngles()* 3.14159265/180.0));
}

double CRegulaPolygon::perimeter() const
{
    double mLenghtEdge=distance((*this)[0], (*this)[1]);
    return countAngles()*mLenghtEdge;
}
