#ifndef CPOLYGON_H
#define CPOLYGON_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <QJsonObject>
#include <cfigureregistry.h>

#define PI 3.14159265

using std::vector;
using std::string;
using glm::vec2;

typedef unsigned int Uint;

class CPolygon
{

public:

    CPolygon(Uint countAngles, const string& name);

    virtual ~CPolygon();

    virtual Uint countAngles() const;

    virtual string getName() const;
    virtual void setName(const string& name);

    virtual QJsonObject toJSON() const = 0;
    virtual const string type() const;

    virtual glm::vec3 toVec3(Uint index) const;

    virtual vec2& operator[] (Uint index);
    virtual const vec2& operator[](Uint index) const;

    virtual double area() const = 0;
    virtual double perimeter () const = 0;

private:
    CPolygon();

    vector<vec2> mAngles;
    string mName;

protected:
    double distance(const vec2& a, const vec2& b) const;

};

#endif // CPOLYGON_H
