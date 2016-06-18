#include "cpolygon.h"



CPolygon::CPolygon(Uint countAngles, const std::string &name): mName(name)
{
    mAngles = vector<vec2>(countAngles);
}

CPolygon::~CPolygon() {}

Uint CPolygon::countAngles() const {return mAngles.size();}

std::string CPolygon::getName() const {return mName;}

void CPolygon::setName(const std::string &name) { mName=name;}

const std::string CPolygon::type() const {return "class CPolygon";}

glm::vec3 CPolygon::toVec3(Uint index) const {return glm::vec3(mAngles[index], 0.0);}

glm::vec2 &CPolygon::operator[](Uint index) {return mAngles[index];}

const glm::vec2 &CPolygon::operator[](Uint index) const {return mAngles[index];}

std::shared_ptr<std::vector<glm::vec3> > CPolygon::getTriangles() const
{
    std::shared_ptr< std::vector<glm::vec3> > v( new std::vector<glm::vec3>( (countAngles()-2)*3) );
    for (Uint i = 1; i < countAngles()-1; i++)
    {
        v->push_back(toVec3(0));
        v->push_back(toVec3(i));
        v->push_back(toVec3(i+1));
    }
    return v;
}

double CPolygon::distance(const glm::vec2 &a, const glm::vec2 &b) const
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
