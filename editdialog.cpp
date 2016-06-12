#include "editdialog.h"
#include "ui_editdialog.h"
#include <QDebug>
#include <QJsonDocument>
#include <cfigureregistry.h>
#include <QMessageBox>

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

}

EditDialog::~EditDialog()
{
    delete ui;
}

//void EditDialog::on_buttonBox_accepted()
//{
//    QString data = ui->plainTextEdit->toPlainText();

//    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

//    QJsonObject fObj = doc.object();
//    mFigureObj = CFigureRegistry::get<CFigure>(fObj.find("type").value().toString().toStdString())(fObj);

//    if(mFigureObj == nullptr)
//        return;

//    qDebug() << "on_buttonBox_accepted";
//}

//void EditDialog::on_buttonBox_rejected()
//{
//    mFigureObj = nullptr;
//    qDebug() << "on_buttonBox_rejected";
//}

void EditDialog::on_EditDialog_finished(int result)
{
    (void)result;
    mFigureObj = nullptr;
    qDebug() << "on_EditDialog_finished";
}

void EditDialog::on_plainTextEdit_textChanged()
{

}

QJsonObject EditDialog::figureObject() const
{
    return mFigureObject;
}

void EditDialog::setFigureObject(const QJsonObject &figureObject)
{
    mFigureObject = figureObject;

    QJsonDocument doc(figureObject);
    QByteArray bytes = doc.toJson();
    QString fig(bytes);
    ui->plainTextEdit->setPlainText(fig);

    //QJsonObject obj()
}

std::shared_ptr<CFigure> EditDialog::getObjectFigure()
{
    return mFigureObj;
}

void EditDialog::on_pushButton_2_clicked()
{
    QString data = ui->plainTextEdit->toPlainText();

    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

    QJsonObject fObj = doc.object();
    mFigureObj = CFigureRegistry::get<CFigure>(fObj.find("type").value().toString().toStdString())(fObj);

    if(mFigureObj == nullptr)
    {
        QMessageBox::information(this,"Error!","Figure isn't correct");
        return;
    }

    mFigureObj = CFigureRegistry::get<CFigure>(fObj.find("type").value().toString().toStdString())(fObj);

    this->setVisible(0);
}

void EditDialog::on_pushButton_clicked()
{
    mFigureObj=nullptr;
    this->setVisible(0);
}
