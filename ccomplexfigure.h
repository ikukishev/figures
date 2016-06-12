#ifndef CCOMPLEXFIGURE_H
#define CCOMPLEXFIGURE_H

#include <cfigure.h>

class CComplexFigure: public CFigure
{
    DECLARE_FIGURE
public:
    CComplexFigure();
    CComplexFigure(const string& name);

    virtual uint countFigures() const {return mFigures.size();}

    static std::shared_ptr<CComplexFigure> load(const QJsonObject& object);
    virtual QJsonObject toJSON() const;

    bool addFigure(std::shared_ptr<CFigure> figure);
    bool replaceFigure(uint index, std::shared_ptr<CFigure> figure);
    bool deleteFigure(uint pos);

    std::shared_ptr<CFigure> operator ()(Uint index) const;

private:
    std::vector<std::shared_ptr<CFigure>> mFigures;
    virtual Uint countVertex() const;
    virtual Uint countEdge() const;
    virtual Uint countFacets() const;

    virtual double surfaceArea() const;
    virtual double volume() const;

protected:
    virtual glm::vec3 getCalculatedVertex(Uint index) const;
};

#endif // CCOMPLEXFIGURE_H
