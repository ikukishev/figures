#include "cfigureparser.h"
#include <QFile>
#include <QJsonDocument>

CFigureParser::CFigureParser(const std::string &name)
    : mNameFile(name)
{}

CFigureParser::CFigureParser()
    : mNameFile("none")
{}

bool CFigureParser::save(const QJsonObject &obj)
{
    if(mNameFile!="none")
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
    if(mNameFile!="none")
    {
        QFile jsonFile(QString::fromStdString(mNameFile));

        jsonFile.open(QFile::ReadOnly);

        QJsonDocument doc;
        doc.fromJson(jsonFile.readAll());
        jsonFile.close();
        obj=doc.object();
    }
    return obj;
}

std::shared_ptr<CFigure> CFigureParser::getObject()
{
    if(!getJSON().isEmpty())
        return nullptr;

    std::shared_ptr<CFigure> figure = CFigureRegistry::get<CFigure>( getJSON()["type"].toString().toStdString() )(getJSON());
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
