#include "cpyramid.h"
#include "ctriangle.h"
#include "cregulapolygon.h"
#include "QJsonDocument"

REGISTER_FIGURE(CPyramid)

inline bool printCPyramid()
{
    std::cout<<"CPyramid" << " ";
    return true;
}

bool sssss= printCPyramid();

CPyramid::CPyramid(double height, std::shared_ptr<CPolygon> basis, const std::string &name)
    :CFigure(basis, name)
{
    mHeight=height;
}

double CPyramid::surfaceArea() const
{
    /* glm::vec3 middlePoint;
    middlePoint.x=(getCalculatedVertex(0).x+getCalculatedVertex(1).x)/2.0;
    middlePoint.y=(getCalculatedVertex(0).y+getCalculatedVertex(1).y)/2.0;
    double apothem = distance(middlePoint, getCalculatedVertex(4));
    return (getBasis()->perimeter()*apothem)/2.0+getBasis()->area();*/

    double lEdgeArea=0; //local edge area

    for(uint i(0); i<getBasis()->countAngles()-1; i++)
        lEdgeArea+=calculatedArea(getCalculatedVertex(i), getCalculatedVertex(4), getCalculatedVertex(i+1));
    lEdgeArea+=calculatedArea(getCalculatedVertex(getBasis()->countAngles()-1), getCalculatedVertex(4), getCalculatedVertex(0));

    return lEdgeArea+getBasis()->area();
}

double CPyramid::volume() const
{
    return 1/3.0*getBasis()->area()*mHeight;
}

QJsonObject CPyramid::toJSON() const
{
    QJsonObject obj;
    obj.insert("name", QString::fromStdString(getName()));
    obj.insert("basis", getBasis()->toJSON());
    obj.insert("height", mHeight);
    obj.insert("type", QString::fromStdString(type()));
    return obj;
}

std::shared_ptr<CPyramid> CPyramid::load(const QJsonObject &object)
{
    return nullptr;
}

Uint CPyramid::countVertex() const {return getBasis()->countAngles()+1;}

Uint CPyramid::countEdge() const {return countVertex()*2;}

Uint CPyramid::countFacets() const {return countVertex()+1;}

double CPyramid::getHeight() const
{
    return mHeight;
}

void CPyramid::setHeight(double height)
{
    mHeight = height;
}

glm::vec3 CPyramid::getCalculatedVertex(Uint index) const
{
    if(index == getBasis()->countAngles())
    {
        return glm::vec3(0,0,mHeight);
    }
    return getBasis()->toVec3(index);
}
