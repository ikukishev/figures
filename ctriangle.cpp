#include "ctriangle.h"

CTriangle::CTriangle(const glm::vec2 &pointA, const glm::vec2 &pointB, const glm::vec2 &pointC, const std::string &name)
   : CPolygon(3, name)
{
   (*this)[0]=pointA;
   (*this)[1]=pointB;
   (*this)[2]=pointC;
}

double CTriangle::perimeter() const
{
   double sum=0;
   for(Uint i(0); i<2; i++)
      sum+=distance((*this)[i], (*this)[i+1]);
   sum=sum+distance((*this)[countAngles()-1], (*this)[0]);
   return sum;
}

double CTriangle::area() const
{
   double lArea=0;
   double per = perimeter()/2.0;

   lArea = sqrt(per*((per-distance((*this)[0], (*this)[1])) * (per-distance( (*this)[1], (*this)[2]) )*(per-distance((*this)[2], (*this)[0]) ) ));

   return lArea;
}
