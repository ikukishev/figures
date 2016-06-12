#ifndef CFIGUREPARSER_H
#define CFIGUREPARSER_H

#include "cfigure.h"

class CFigureParser
{
public:
    CFigureParser();
    CFigureParser(const string& name);

    bool save(const QJsonObject& obj);

    QJsonObject getJSON();

    std::shared_ptr<CFigure> getObject();
    std::shared_ptr<CFigure> getObject(const QJsonObject& obj );

    string getNameFile() const;
    void setNameFile(const string &nameFile);

private:
    string mNameFile;
};

#endif // CFIGUREPARSER_H
