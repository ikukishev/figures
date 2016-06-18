#include "cprism.h"

REGISTER_FIGURE(CPrism)

inline bool printCPrism()
{
    std::cout<<"//CPrism" << " ";
    return true;
}

bool ssss= printCPrism();

CPrism::CPrism(std::shared_ptr<CPolygon> basis, double height, std::string name)
    : CFigure(basis, name)
{
    mHeight=height;
}

double CPrism::surfaceArea() const
{
    double areaEdge=0;
    uint cBasis=getBasis()->countAngles();

    for(uint i(0), j(cBasis); i<cBasis-1; i++, j++)
        areaEdge+=distance(getCalculatedVertex(i), getCalculatedVertex(j))*distance(getCalculatedVertex(i), getCalculatedVertex(i+1));

    areaEdge+=distance(getCalculatedVertex(cBasis-1), getCalculatedVertex(countVertex()-1))*distance(getCalculatedVertex(cBasis-1), getCalculatedVertex(0));
    return areaEdge+getBasis()->area()*2;
}

double CPrism::volume() const
{
    return getBasis()->area()*mHeight;
}

QJsonObject CPrism::toJSON() const
{
    QJsonObject obj;
    obj.insert("type", QString::fromStdString(type()));
    obj.insert("basis", getBasis()->toJSON());
    obj.insert("height", mHeight);
    obj.insert("name", QString::fromStdString(getName()));
    return obj;
}

Uint CPrism::countVertex() const {return getBasis()->countAngles()*2;}

Uint CPrism::countEdge() const {return getBasis()->countAngles()*3;}

Uint CPrism::countFacets() const { return getBasis()->countAngles()+2;}

glm::vec3 CPrism::getCalculatedVertex(Uint index) const
{
    uint cAngles = getBasis()->countAngles();
    if(index >= cAngles && index<cAngles*2)
    {
        glm::vec3 vertex(getBasis()->toVec3(index-cAngles));
        vertex.z=mHeight;
        return vertex;
    }
    return getBasis()->toVec3(index);
}

double CPrism::getHeight() const
{
    return mHeight;
}

void CPrism::setHeight(double height)
{
    mHeight = height;
}

std::shared_ptr<CPrism> CPrism::load(const QJsonObject &object)
{
    if(object.find("type") == object.end())
       return nullptr;

    if(object.find("type").value().toString() != QString::fromStdString(__static_type_name__))
       return nullptr;

    if(object.find("basis")==object.end())
        return nullptr;

    if(!object.find("basis").value().isObject())
        return nullptr;

    std::shared_ptr<CPolygon> basis = CFigureRegistry::get<CPolygon>(object.find("basis").value().toObject()["type"].toString().toStdString())(object.find("basis").value().toObject());

    if(basis == nullptr)
        return nullptr;

    if(object.find("height") == object.end())
        return nullptr;

    if(!object.find("height").value().isDouble())
        return nullptr;

    double height = object.find("height").value().toDouble();


    if(object.find("name") == object.end())
        return nullptr;

    if(!object.find("name").value().isString())
        return nullptr;

    std::string name = object.find("name").value().toString().toStdString();

    return std::shared_ptr<CPrism>(new CPrism(basis, height, name));
}

DrawData CPrism::getDrawData() const
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
    glm::vec3 aP, bP, cP, dP;

    for (Uint i = 0; i < base->countAngles()-1; i++)
    {
        aP = base->toVec3(i);
        bP = base->toVec3(i+1);
        cP = bP;
        cP.z = (float)mHeight;
        dP = aP;
        dP.z = (float)mHeight;

        v->push_back(aP);
        v->push_back(bP);
        v->push_back(cP);

        v->push_back(aP);
        v->push_back(cP);
        v->push_back(dP);

        colorR = (float)rand()/RAND_MAX;
        colorG = (float)rand()/RAND_MAX;
        colorB = (float)rand()/RAND_MAX;

        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));

        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));
        c->push_back(glm::vec3(colorR, colorG, colorB));
    }

    aP = base->toVec3(0);
    bP = base->toVec3(base->countAngles()-1);
    cP = bP;
    cP.z = (float)mHeight;
    dP = aP;
    dP.z = (float)mHeight;

    v->push_back(aP);
    v->push_back(bP);
    v->push_back(cP);

    v->push_back(aP);
    v->push_back(cP);
    v->push_back(dP);

    colorR = (float)rand()/RAND_MAX;
    colorG = (float)rand()/RAND_MAX;
    colorB = (float)rand()/RAND_MAX;

    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));

    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));
    c->push_back(glm::vec3(colorR, colorG, colorB));

    for (Uint i = 0; i < bt->size(); i++)
    {
        glm::vec3 lVec = bt->operator [](i);
        lVec.z=(float)mHeight;
        v->push_back(lVec);
        c->push_back(glm::vec3(1.0f, 1.0f, 0.0));
    }

    return DrawData(v,c);
}

