#ifndef CDODECAHEDRON_H
#define CDODECAHEDRON_H

#include <cfigure.h>
#include "cregulapolygon.h"

class CDodecahedron: public CFigure
{
   DECLARE_FIGURE
private:
    double mLenght;
    virtual glm::vec3 operator [](Uint index) const;

public:
    CDodecahedron(double lenght, const std::string& name);
    static std::shared_ptr<CDodecahedron> load(const QJsonObject& object);

    virtual double surfaceArea() const;
    virtual double volume() const;
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
