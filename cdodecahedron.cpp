#include "cdodecahedron.h"
#include "glm/gtc/matrix_transform.hpp"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

REGISTER_FIGURE(CDodecahedron)

inline bool printCDodecahedron()
{
    std::cout<<"//CDodecahedron" << " ";
    return true;
}

bool sss= printCDodecahedron();


double CDodecahedron::getLenght() const
{
    return mLenght;
}

CDodecahedron::CDodecahedron(double lenght, const std::string &name)
    : CFigure(std::shared_ptr<CPolygon>(0), name), mLenght(lenght)
{
    CRegulaPolygon rp(glm::vec2(0, 0), 0, lenght, 5, "none");

    std::shared_ptr<CPolygon> bs = CFigureRegistry::get<CPolygon>(rp.type())(rp.toJSON());
    setBasis(bs);

}

std::shared_ptr<CDodecahedron> CDodecahedron::load(const QJsonObject &object)
{
    if(object.find("type") == object.end())
       return nullptr;
    if(object.find("type").value().toString() != QString::fromStdString(__static_type_name__))
       return nullptr;

    if(object.find("lenght") == object.end())
        return nullptr;

    if(!object.find("lenght").value().isDouble())
        return nullptr;

    if(object.find("lenght").value().toDouble() <= 0)
        return nullptr;

    double lenght = object.find("lenght").value().toDouble();

    if(object.find("name") == object.end())
        return nullptr;

    if(!object.find("name").value().isString())
        return nullptr;

    std::string name = object.find("name").value().toString().toStdString();

    return std::shared_ptr<CDodecahedron>(new CDodecahedron(lenght, name));
}

double CDodecahedron::surfaceArea() const
{
    return 20.65*mLenght*mLenght;
}

double CDodecahedron::volume() const
{
    return 7.66*mLenght*mLenght*mLenght;
}

glm::vec3 CDodecahedron::operator [](Uint index) const
{
    return glm::vec3(0);
}

QJsonObject CDodecahedron::toJSON() const
{
    QJsonObject obj;
    obj.insert("name", QString::fromStdString(getName()));
    obj.insert("type", QString::fromStdString(type()));
    obj.insert("lenght", mLenght);
    return obj;
}

Uint CDodecahedron::countVertex() const
{
    return 20;
}

Uint CDodecahedron::countEdge() const
{
    return 30;
}

Uint CDodecahedron::countFacets() const
{
    return 12;
}

DrawData CDodecahedron::getDrawData() const
{
    std::shared_ptr< std::vector<glm::vec3> > v( new std::vector<glm::vec3>() );
    std::shared_ptr< std::vector<glm::vec3> > c( new std::vector<glm::vec3>() );

    std::shared_ptr<CPolygon> base = getBasis();

    float radiusInsideSphere = (mLenght/4)*((1+sqrt(5))*sqrt(3) + sqrt(10+22/sqrt(5)))/2;
    radiusInsideSphere+=radiusInsideSphere*0.04;

    auto addPoints = [&](const std::vector<glm::vec3>& polygon)
    {
        float colorR = (float)rand()/RAND_MAX;
        float colorG = (float)rand()/RAND_MAX;
        float colorB = (float)rand()/RAND_MAX;

        for (Uint i = 1; i < polygon.size()-1; i++)
        {
            v->push_back(polygon[0]); // = base->toVec3(i);
            v->push_back(polygon[i]);
            v->push_back(polygon[i+1]);

            c->push_back(glm::vec3(colorR, colorG, colorB));
            c->push_back(glm::vec3(colorR, colorG, colorB));
            c->push_back(glm::vec3(colorR, colorG, colorB));
        }
    };

    std::vector<glm::vec3> baseFace(5);
    for (Uint i = 0; i < baseFace.size(); i++)
    {
        baseFace[i] = base->toVec3(i);
        baseFace[i].z = -radiusInsideSphere;
    }
    addPoints(baseFace);

    float angle = acos(-1/sqrt(5))*180/M_PI;

    std::vector<glm::vec3> face(5);

    auto calcFace = [&](const glm::vec3& p1, const glm::vec3& p2, float angleValue)
    {
        glm::mat4 mat = glm::translate(glm::mat4(1.0f), p1-glm::vec3(0,0,0) );
        mat = glm::rotate( mat, angleValue, p1-p2 );
        mat = glm::translate(mat, glm::vec3(0,0,0)-p1 );
        for (Uint j = 0; j < face.size(); j++)
        {
            face[j] = glm::vec3(mat*glm::vec4(baseFace[j], 1.0f));
        }
        addPoints(face);
    };

    for(Uint i = 0; i < baseFace.size()-1; i++)
    {
        calcFace(baseFace[i], baseFace[i+1], -angle);
    }
    calcFace(baseFace[baseFace.size()-1], baseFace[0], -angle);

    glm::mat4 mat = glm::rotate(glm::mat4(1.0f), 36.0f, glm::vec3(0,0,1) );
    for (Uint i = 0; i < baseFace.size(); i++)
    {
        baseFace[i] = glm::vec3(mat*glm::vec4(base->toVec3(i), 1.0f));
        baseFace[i].z = radiusInsideSphere;
    }
    addPoints(baseFace);

    for(Uint i = 0; i < baseFace.size()-1; i++)
    {
        calcFace(baseFace[i], baseFace[i+1], angle);
    }
    calcFace(baseFace[baseFace.size()-1], baseFace[0], angle);


    return DrawData(v,c);
}

glm::vec3 CDodecahedron::getCalculatedVertex(Uint index) const {return glm::vec3(0);}
