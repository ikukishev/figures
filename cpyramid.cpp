#include "cpyramid.h"
#include "ctriangle.h"
#include "cregulapolygon.h"
#include "QJsonDocument"

REGISTER_FIGURE(CPyramid)

inline bool printCPyramid()
{
    std::cout<<"//CPyramid" << " ";
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
    if(object.find("type") == object.end())
        return nullptr;
    if(object.find("type").value().toString().toStdString() != __static_type_name__)
        return nullptr;

    if(object.find("basis") == object.end())
        return nullptr;

    if(!object.find("basis").value().isObject())
        return nullptr;

    std::shared_ptr<CPolygon> basis = CFigureRegistry::get<CPolygon>( object.find("basis").value().toObject()["type"].toString().toStdString() )( object.find("basis").value().toObject() );

    if(basis == nullptr)
        return nullptr;

    if(object.find("height") == object.end())
        return nullptr;

    if(!object.find("height").value().isDouble())
        return nullptr;

    if(object.find("height").value().toDouble() <= 0)
        return nullptr;

    double height = object.find("height").value().toDouble();

    if(object.find("name") == object.end())
        return nullptr;

    if(!object.find("name").value().isString())
        return nullptr;

    std::string name = object.find("name").value().toString().toStdString();

    return std::shared_ptr<CPyramid>(new CPyramid(height, basis, name));
}

Uint CPyramid::countVertex() const {return getBasis()->countAngles()+1;}

Uint CPyramid::countEdge() const {return countVertex()*2;}

Uint CPyramid::countFacets() const {return countVertex();}

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

DrawData CPyramid::getDrawData() const
{
    std::shared_ptr< std::vector<glm::vec3> > v( new std::vector<glm::vec3>() );
    std::shared_ptr< std::vector<glm::vec3> > c( new std::vector<glm::vec3>() );

    std::shared_ptr<CPolygon> base = getBasis();
    std::shared_ptr<std::vector<glm::vec3> > bt = base->getTriangles();

    for (Uint i = 0; i < bt->size(); i++)
    {
        v->push_back(bt->operator [](i));
        c->push_back(glm::vec3(1.0f, 0.0, 0.0));
    }

    float colorR, colorG, colorB;
    glm::vec3 aP, bP, cP;
    cP = bP;
    cP.z = (float)mHeight;

    for (Uint i = 0; i < base->countAngles()-1; i++)
    {
        aP = base->toVec3(i);
        bP = base->toVec3(i+1);


        v->push_back(aP);
        v->push_back(bP);
        v->push_back(cP);

        colorR = (float)rand()/RAND_MAX;
        colorG = (float)rand()/RAND_MAX;
        colorB = (float)rand()/RAND_MAX;

        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));

    }

    aP = base->toVec3(0);
    bP = base->toVec3(base->countAngles()-1);

    v->push_back(aP);
    v->push_back(bP);
    v->push_back(cP);

    colorR = (float)rand()/RAND_MAX;
    colorG = (float)rand()/RAND_MAX;
    colorB = (float)rand()/RAND_MAX;

    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));

    return DrawData(v,c);
}
