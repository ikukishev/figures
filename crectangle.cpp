#include "crectangle.h"



CRectangle::CRectangle(glm::vec2 downLeftAngle, double length, double width, const std::string &name)
   : CPolygon(4, name)
{
    (*this)[0]=downLeftAngle;

    (*this)[1].x=0;
    (*this)[1].y=width;

    (*this)[2].x=length;
    (*this)[2].y=width;

    (*this)[3].x=length;
   (*this)[3].y=0;
}

double CRectangle::area() const
{
    if(countAngles())
    {
        return distance((*this)[0], (*this)[1])*distance((*this)[1], (*this)[2]);
    }
    else return 0;
}

double CRectangle::perimeter() const
{
   if(countAngles()){
      return distance((*this)[0], (*this)[1])*2+2*distance((*this)[1], (*this)[2]);
   }
   else return 0;
}
