#ifndef CPRISM_H
#define CPRISM_H

#include "cfigure.h"

class CPrism: public CFigure
{
    DECLARE_FIGURE
public:
    CPrism(std::shared_ptr<CPolygon> basis, double height, std::string name);

    double surfaceArea() const;
    double volume() const;

    QJsonObject toJSON() const;

    Uint countVertex() const;
    Uint countEdge() const;
    Uint countFacets() const;

    double getHeight() const;
    void setHeight(double height);
    static std::shared_ptr<CPrism> load(const QJsonObject& object);

protected:
    glm::vec3 getCalculatedVertex(Uint index) const;

private:
    double mHeight;

};

#endif // CPRISM_H
