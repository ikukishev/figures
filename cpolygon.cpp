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

double CPolygon::distance(const glm::vec2 &a, const glm::vec2 &b) const
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
