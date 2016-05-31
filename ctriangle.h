#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "cpolygon.h"

class CTriangle: public CPolygon
{
   DECLARE_FIGURE
private:
   CTriangle();
public:

    CTriangle( const glm::vec2& pointA, const glm::vec2& pointB, const glm::vec2& pointC, const std::string& name);

    virtual QJsonObject toJSON() const;
    static std::shared_ptr<CTriangle> load(const QJsonObject& object);

    virtual double perimeter () const;    
    virtual double area() const;
};

#endif // CTRIANGLE_H
