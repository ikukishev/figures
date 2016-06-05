#include "cregulapolygon.h"
#include <QJsonArray>

REGISTER_FIGURE(CRegulaPolygon)

inline bool printCRegulaPolygon()
{
    std::cout<<"CRegulaPolygon" << " ";
    return true;
}

bool ssssss= printCRegulaPolygon();

CRegulaPolygon::CRegulaPolygon(const glm::vec2 &centerPoint, double startAngle, double radius, int countAngles, const std::string &name)
    : mStartAngle(startAngle), mCenter(centerPoint), CPolygon(countAngles, name)
{
    double ang=startAngle, dAngle=360.0/countAngles;
    for(int i(0); i<countAngles; i++)
    {
        (*this)[i].x=radius*cos(ang*PI/180.0)+centerPoint.x;
        (*this)[i].y=radius*sin(ang*PI/180.0)+centerPoint.y;
        ang+=dAngle;
    }
}

std::shared_ptr<CRegulaPolygon> CRegulaPolygon::load(const QJsonObject &object)
{
    if(object.find("type")==object.end())
        return nullptr;

    if(object.find("type").value().toString().toStdString()!=__static_type_name__)
        return nullptr;

    if(object.find("name")==object.end())
        return nullptr;

    if(!object.find("name").value().isString())
        return nullptr;

    string name = object.find("name").value().toString().toStdString();

    if(object.find("radius")==object.end())
        return nullptr;

    if(!object.find("radius").value().isDouble())
        return nullptr;

    double radius = object.find("radius").value().toDouble();

    if(object.find("start angle")==object.end())
        return nullptr;

    if(!object.find("start angle").value().isDouble())
        return nullptr;

    double sA = object.find("start angle").value().toDouble();

    if(object.find("count angles")==object.end())
        return nullptr;

    if(!object.find("count angles").value().isDouble())
        return nullptr;

    int cAngles = object.find("count angles").value().toInt();

    if(object.find("center")==object.end())
        return nullptr;

    if(!object.find("center").value().isArray())
        return nullptr;

    QJsonArray arr;
    arr=object.find("center").value().toArray();

    vec2 center;
    center.x = arr[0].toDouble();
    center.y = arr[1].toDouble();

    return std::shared_ptr<CRegulaPolygon>(new CRegulaPolygon(center, sA, radius, cAngles, name));

}

QJsonObject CRegulaPolygon::toJSON() const
{
    QJsonObject obj;
    obj.insert("name", QString::fromStdString(getName()));
    obj.insert("type", QString::fromStdString(type()));
    obj.insert("radius", getRadius());
    obj.insert("start angle", mStartAngle);
    QJsonArray arr;
    arr.insert(0, mCenter.x);
    arr.insert(1, mCenter.y);
    obj.insert("center", arr);
    obj.insert("count angles", (int)countAngles());
    return obj;
}

double CRegulaPolygon::getRadius() const
{
   return distance(mCenter, (*this)[0]);
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
