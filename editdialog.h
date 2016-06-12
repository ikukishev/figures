#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <cfigure.h>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();

    QJsonObject figureObject() const;
    void setFigureObject(const QJsonObject &figureObject);
    std::shared_ptr<CFigure> getObjectFigure();

private slots:/*
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();*/

    void on_EditDialog_finished(int result);

    void on_plainTextEdit_textChanged();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditDialog *ui;
    QJsonObject mFigureObject;
    std::shared_ptr<CFigure> mFigureObj;
};

#endif // EDITDIALOG_H
