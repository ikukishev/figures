#include "ccomplexfigure.h"
#include "QJsonArray"
#include <QDebug>

REGISTER_FIGURE(CComplexFigure)

CComplexFigure::CComplexFigure()
    : CFigure(std::shared_ptr<CPolygon>(0), "none")
{
    mFigures = std::vector< std::shared_ptr<CFigure> >(0);

}

CComplexFigure::CComplexFigure(const string& name)
    : CFigure(std::shared_ptr<CPolygon>(0), name)
{
    mFigures = std::vector< std::shared_ptr<CFigure> >(0);

}


//CComplexFigure::CComplexFigure(std::vector< std::shared_ptr<CFigure> > figures)
//{
//    mFigures = figures;
//}

std::shared_ptr<CComplexFigure> CComplexFigure::load(const QJsonObject &object)
{
    if(object.find("type") == object.end())
        return nullptr;

    if(object.find("type").value().toString()!=QString::fromStdString(__static_type_name__))
        return nullptr;

    if(object.find("name") == object.end())
        return nullptr;

    if(!object.find("name").value().isString())
        return nullptr;

    std::string name = object.find("name").value().toString().toStdString();

    if(object.find("figures")==object.end())
        return nullptr;

    if(!object.find("figures").value().isArray())
        return nullptr;

    QJsonArray arr;
    arr=object.find("figures").value().toArray();
    if (arr.size() == 0)
        return nullptr;

    std::vector<std::shared_ptr<CFigure> > fig;

    for(uint i(0); i<arr.size(); i++)
    {
       std::shared_ptr<CFigure> lFigure = CFigureRegistry::get<CFigure>(arr[i].toObject()["type"].toString().toStdString() )( arr[i].toObject() );
       qDebug() << arr[i].toObject()["type"].toString();
       qDebug() << arr[i].toObject()["name"].toString();
        fig.push_back( lFigure);
    }

    CComplexFigure list(name);
    for(uint i(0); i<fig.size(); i++)
        list.addFigure(fig[i]);

    return std::shared_ptr<CComplexFigure>(new CComplexFigure(list));
}

bool CComplexFigure::addFigure(std::shared_ptr<CFigure> figure)
{
    if(figure == nullptr) return false;
    for(uint i(0); i<countFigures(); i++)
        if(figure->getName() == mFigures[i]->getName()) return false;

    mFigures.push_back(figure);
    return true;
}

bool CComplexFigure::deleteFigure(uint pos)
{
    if(pos >= countFigures()) return false;
    mFigures.erase(mFigures.begin()+pos);
    return true;
}


std::shared_ptr<CFigure>& CComplexFigure::operator ()(Uint index)
{
    return mFigures[index];
}

DrawData CComplexFigure::getDrawData() const
{
    return DrawData();
}

QJsonObject CComplexFigure::toJSON() const
{
    QJsonObject obj;
    obj.insert("type", QString::fromStdString(type()));
    QJsonArray arr;
    for(uint i(0); i<mFigures.size(); i++)
    {
        arr.insert(i, mFigures[i]->toJSON());
    }
    obj.insert("figures", arr);
    obj.insert("name", QString::fromStdString(getName()));
    return obj;
}

bool CComplexFigure::replaceFigure(uint index, std::shared_ptr<CFigure> figure)
{
    if(index>=countFigures()) return false;

    for(uint i(0); i<countFigures(); i++)
        if(figure->getName() == mFigures[i]->getName())
           if(index != i)return false;

    mFigures[index]=figure;
    return true;
}

Uint CComplexFigure::countVertex() const {return 0;}

Uint CComplexFigure::countEdge() const {return 0;}

Uint CComplexFigure::countFacets() const {return 0;}

double CComplexFigure::surfaceArea() const {return 0;}

double CComplexFigure::volume() const {return 0;}

glm::vec3 CComplexFigure::getCalculatedVertex(Uint index) const {return glm::vec3(0);}
