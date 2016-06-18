#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <cfigure.h>

class CPyramid: public CFigure
{
    DECLARE_FIGURE
public:
    CPyramid(double height, std::shared_ptr<CPolygon> basis, const std::string& name);

    virtual double surfaceArea() const;
    virtual double volume() const;

    QJsonObject toJSON() const;
    static std::shared_ptr<CPyramid> load(const QJsonObject& object);

    virtual Uint countVertex() const;
    virtual Uint countEdge() const;
    virtual Uint countFacets() const;

    double getHeight() const;
    void setHeight(double height);

    virtual DrawData getDrawData() const;

protected:
    glm::vec3 getCalculatedVertex(Uint index) const;

private:
    CPyramid();
    double mHeight;

};

#endif // CPYRAMID_H
