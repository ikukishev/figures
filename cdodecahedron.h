#ifndef CDODECAHEDRON_H
#define CDODECAHEDRON_H

#include <cfigure.h>
#include "cregulapolygon.h"

class CDodecahedron: public CFigure
{
   DECLARE_FIGURE
private:
    class CPlaneOfSymmetry
    {
    public:
        CPlaneOfSymmetry(const CRegulaPolygon& pentagon);

        glm::vec3 operator[](uint index) const;
        CPlaneOfSymmetry& transform(glm::mat4 matrix);

    private:
        vector<glm::vec3> mPoints;

        double distanceSymm(const vec2& a, const vec2& b) const
        {
             return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
        }

        glm::vec2 setRightPosition(glm::vec2 point, double angle);
    };

    double mLenght;
    vector<glm::vec3> mPoints;

public:
    CDodecahedron(double lenght, const std::string& name);
    static std::shared_ptr<CDodecahedron> load(const QJsonObject& object);

    virtual double surfaceArea() const;
    virtual double volume() const;
    virtual glm::vec3 operator [](Uint index) const;
    virtual QJsonObject toJSON() const;
    virtual Uint countVertex() const;
    virtual Uint countEdge() const;
    virtual Uint countFacets() const;
    virtual DrawData getDrawData() const;

    double getLenght() const;

protected:
    virtual glm::vec3 getCalculatedVertex(Uint index) const;
};

#endif // CDODECAHEDRON_H
