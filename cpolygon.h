#ifndef CPOLYGON_H
#define CPOLYGON_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cmath>

#define PI 3.14159265

using std::vector;
using std::string;
using glm::vec2;

typedef unsigned int Uint;

class CPolygon
{
public:

    CPolygon(Uint countAngles, const string& name): mName(name)
    {
        mAngles = vector<vec2>(countAngles);
    }

    virtual ~CPolygon() {}

    virtual Uint countAngles() const {return mAngles.size();}

    virtual string getName() const {return mName;}
    virtual void setName(const string& name) { mName=name;}


    virtual vec2& operator[] (Uint index) {return mAngles[index];}
    virtual const vec2& operator[](Uint index) const {return mAngles[index];}

    virtual double area() const = 0;
    virtual double perimeter () const = 0;

private:
    CPolygon();

    vector<vec2> mAngles;
    string mName;

protected:
    double distance(const vec2& a, const vec2& b) const
    {
       return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
    }

};

#endif // CPOLYGON_H
