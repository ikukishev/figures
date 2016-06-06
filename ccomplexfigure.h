#ifndef CCOMPLEXFIGURE_H
#define CCOMPLEXFIGURE_H

#include <cfigure.h>

class CComplexFigure: public CFigure
{
    DECLARE_FIGURE
public:
    CComplexFigure(const string& name);
    //CComplexFigure( std::vector<std::shared_ptr<CFigure>> figures);

    static std::shared_ptr<CComplexFigure> load(const QJsonObject& object);
    void addFigure(std::shared_ptr<CFigure> figure);
    void deleteFigure(uint pos);
    std::shared_ptr<CFigure> operator ()(Uint index) const;
    virtual QJsonObject toJSON() const;

private:
    std::vector<std::shared_ptr<CFigure>> mFigures;
    virtual Uint countVertex() const;
    virtual Uint countEdge() const;
    virtual Uint countFacets() const;
    // CFigure interface
    virtual double surfaceArea() const;
    virtual double volume() const;


protected:
    virtual glm::vec3 getCalculatedVertex(Uint index) const;
};

#endif // CCOMPLEXFIGURE_H
