#ifndef CFIGURE_H
#define CFIGURE_H

#include <string>
#include <cpolygon.h>

class DrawData
{
public:
    DrawData();
    DrawData(const std::shared_ptr< std::vector<glm::vec3> > &vertexes
             , const std::shared_ptr< std::vector<glm::vec3> > &colors);

    DrawData(std::vector<glm::vec3> * vertexes
             , std::vector<glm::vec3> * colors);

    std::shared_ptr< std::vector<glm::vec3> > getVertexes() const
    {
        return mVertexes;
    }

    std::shared_ptr< std::vector<glm::vec3> > getColores() const
    {
        return mColors;
    }


private:
    std::shared_ptr< std::vector<glm::vec3> > mVertexes;
    std::shared_ptr< std::vector<glm::vec3> > mColors;

};

class CFigure
{
public:

    CFigure(std::shared_ptr<CPolygon> basis, const std::string& name);

    virtual ~CFigure();

    virtual double surfaceArea() const  = 0;
    virtual double volume() const = 0;

    virtual void setMatrix(const glm::mat4& mat);
    virtual glm::mat4 getMatrix() const;

    virtual glm::vec3 operator[](Uint index) const;    
    //virtual std::shared_ptr<CFigure> operator()(Uint index) const {return nullptr;}

    virtual QJsonObject toJSON() const = 0;
    virtual const std::string type() const;

    virtual std::string getName() const;
    virtual void setName(const std::string& name);

    virtual Uint countVertex() const= 0;
    virtual Uint countEdge() const = 0; //кол-во ребер
    virtual Uint countFacets() const = 0; //кол-во граней

    std::shared_ptr<CPolygon> getBasis() const;

    virtual DrawData getDrawData() const = 0;

protected:
    virtual glm::vec3 getCalculatedVertex(Uint index) const = 0;
    virtual void setBasis(const std::shared_ptr<CPolygon> &basis);
    double distance(glm::vec3 a, glm::vec3 b) const;
    double calculatedArea(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) const;
private:
    std::string mNameFigure;
    glm::mat4 mMat;
    std::shared_ptr<CPolygon> mBasis;
};

#endif // CFIGURE_H
