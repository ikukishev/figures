#include "cfigureparser.h"
#include <QFile>
#include <QJsonDocument>

CFigureParser::CFigureParser(const std::string &name)
    : mNameFile(name)
{}

CFigureParser::CFigureParser()
    : mNameFile("")
{}

bool CFigureParser::save(const QJsonObject &obj)
{
    if(mNameFile!="")
    {
        QJsonDocument doc;
        doc.setObject(obj);

        QFile jsonFile(QString::fromStdString(mNameFile));

        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(doc.toJson());
        jsonFile.close();
        return 1;
    }
    return 0;
}

QJsonObject CFigureParser::getJSON()
{

    QJsonObject obj;
    if(mNameFile!="")
    {
        QFile jsonFile(QString::fromStdString(mNameFile));
        QJsonDocument doc;

        jsonFile.open(QFile::ReadOnly);

        obj=doc.fromJson(jsonFile.readAll()).object();
        jsonFile.close();
    }
    return obj;
}

std::shared_ptr<CFigure> CFigureParser::getObject()
{
    if(getJSON().isEmpty())
        return nullptr;

    std::shared_ptr<CFigure> figure = CFigureRegistry::get<CFigure>( getJSON().find("type").value().toString().toStdString() )( getJSON() );
    return figure;
}

std::shared_ptr<CFigure> CFigureParser::getObject(const QJsonObject& obj)
{
    if(obj.find("type") == obj.end())
        return nullptr;

    if(!obj.find("type").value().isString())
        return nullptr;

    std::shared_ptr<CFigure> figure = CFigureRegistry::get<CFigure>( obj.find("type").value().toString().toStdString() )(obj);
    return figure;
}

string CFigureParser::getNameFile() const
{
    return mNameFile;
}

void CFigureParser::setNameFile(const string &nameFile)
{
    mNameFile = nameFile;
}
