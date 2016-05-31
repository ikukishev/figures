#include "ctriangle.h"
#include <QJsonArray>

REGISTER_FIGURE(CTriangle)

CTriangle::CTriangle(const glm::vec2 &pointA, const glm::vec2 &pointB, const glm::vec2 &pointC, const std::string &name)
   : CPolygon(3, name)
{
   (*this)[0]=pointA;
   (*this)[1]=pointB;
   (*this)[2]=pointC;
}

QJsonObject CTriangle::toJSON() const
{
   QJsonObject obj;
   obj.insert("type", QString::fromStdString(type()));
   obj.insert("name", QString::fromStdString(getName()));
   QJsonArray arr;
   arr.insert(0, (*this)[0].x);
   arr.insert(1, (*this)[0].y);
   arr.insert(2, (*this)[1].x);
   arr.insert(3, (*this)[1].y);
   arr.insert(4, (*this)[2].x);
   arr.insert(5, (*this)[2].y);
   obj.insert("points", arr);
   return obj;
}

std::shared_ptr<CTriangle> CTriangle::load(const QJsonObject &object)
{
  // QJsonObject::iterator it = object.find(QString::fromStdString( __static_type_name__));
   if(object.find("type") == object.end())
      return nullptr;

   if(object.find("name") == object.end())
      return nullptr;

   string name;
   vec2 a, b, c;

   if(!object.find("name").value().isString())
      return nullptr;

   name = object.find("name").value().toString().toStdString();

   QJsonArray arr;
   if(object.find("points") == object.end())
      return nullptr;

   arr = object.find("points").value().toArray();
   if(arr.size()!=6)
      return nullptr;

   for(int i(0); i<6; i++)
      if(!arr[i].isDouble())
      return nullptr;

   a.x=arr[0].toDouble();
   a.y=arr[1].toDouble();
   b.x=arr[2].toDouble();
   b.y=arr[3].toDouble();
   c.x=arr[4].toDouble();
   c.y=arr[5].toDouble();

   return std::shared_ptr<CTriangle>(new CTriangle(a, b, c, name));

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
