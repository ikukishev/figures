#include "crectangle.h"
#include <QJsonArray>

REGISTER_FIGURE(CRectangle)

inline bool printRect()
{
    std::cout<<"//rect" << " ";
    return true;
}

bool s=printRect();

CRectangle::CRectangle(glm::vec2 downLeftAngle, double length, double width, const std::string &name)
   : CPolygon(4, name)
{
    (*this)[0]=downLeftAngle;

    (*this)[1].x=downLeftAngle.x;
    (*this)[1].y=downLeftAngle.y+width;

    (*this)[2].x=downLeftAngle.x+length;
    (*this)[2].y=downLeftAngle.y+width;

    (*this)[3].x=downLeftAngle.x+length;
    (*this)[3].y=downLeftAngle.y;
}

QJsonObject CRectangle::toJSON() const
{
   QJsonObject obj;
   obj.insert("type", QString::fromStdString(type()));
   obj["length"]=getLength();
   obj["width"]=getWidth();
   obj["name"]=QString::fromStdString(getName());
   QJsonArray arr;
   arr.push_back((*this)[0].x);
   arr.push_back((*this)[0].y);
   obj["downLeftAngle"]=arr;
   return obj;
}

std::shared_ptr<CRectangle> CRectangle::load(const QJsonObject &object)
{
   if(object.find("type") == object.end())
      return nullptr;
   if(object.find("type").value().toString() != QString::fromStdString(__static_type_name__))
      return nullptr;

   glm::vec2 dLA;
   double length;
   double width;
   string name;

   if(object.find("type") == object.end() )
      return nullptr;
   if(!object.find("type").value().isString() )
      return nullptr;

   QJsonArray arr = object.find("downLeftAngle").value().toArray();
   if(arr.size()!=2) return nullptr;

   if(!arr[0].isDouble() || !arr[1].isDouble())
      return nullptr;

   dLA.x=arr[0].toDouble();
   dLA.y=arr[1].toDouble();

   if(object.find("length") == object.end())
      return nullptr;

   if(!object.find("length").value().isDouble())
      return nullptr;

   if(object.find("length").value().toDouble() <= 0)
      return nullptr;

   length=object.find("length").value().toDouble();

   if(object.find("width") == object.end())
      return nullptr;

   if(!object.find("width").value().isDouble())
      return nullptr;

   if(object.find("width").value().toDouble() <= 0)
      return nullptr;

   width=object.find("width").value().toDouble();

   if(object.find("name") == object.end())
      return nullptr;

   if(!object.find("name").value().isString())
      return nullptr;

   name=object.find("name").value().toString().toStdString();

   return std::shared_ptr<CRectangle>(new CRectangle(dLA, length, width, name));
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

double CRectangle::getWidth() const
{
   return abs((*this)[1].y-(*this)[0].y);
}

double CRectangle::getLength() const
{
   return abs((*this)[2].x-(*this)[1].x);
}

glm::vec2 CRectangle::getDownLeftAngle() const
{
   return (*this)[0];
}

CRectangle &CRectangle::setWidth(double width)
{
   (*this)[1].y=(*this)[0].y+width;
   (*this)[2].y=(*this)[3].y+width;
   return *this;
}

CRectangle &CRectangle::setLength(double length)
{
   (*this)[2].x=(*this)[0].x+length;
   (*this)[3].x=(*this)[0].x+length;
   return *this;
}

CRectangle &CRectangle::setDownLeftAngle(glm::vec2 point)
{
   double length = getLength();
   double width = getWidth();

   (*this)[0]=point;

   (*this)[1].x=point.x;
   (*this)[1].y=point.y+width;

   (*this)[2].x=point.x+length;
   (*this)[2].y=point.y+width;

   (*this)[3].x=point.x+length;
   (*this)[3].y=point.y;

   return *this;
}
