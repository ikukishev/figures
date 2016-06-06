#ifndef CPRISM_H
#define CPRISM_H

#include "cfigure.h"

class CPrism: public CFigure
{
    DECLARE_FIGURE
public:
    CPrism(std::shared_ptr<CPolygon> basis, double height, std::string name);

    virtual double surfaceArea() const;
    virtual double volume() const;

    virtual QJsonObject toJSON() const;

    virtual Uint countVertex() const;
    virtual Uint countEdge() const;
    virtual Uint countFacets() const;

    double getHeight() const;
    void setHeight(double height);
    static std::shared_ptr<CPrism> load(const QJsonObject& object);

protected:
    virtual glm::vec3 getCalculatedVertex(Uint index) const;

private:
    double mHeight;

};

#endif // CPRISM_H
