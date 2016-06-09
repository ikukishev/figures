#include "editdialog.h"
#include "ui_editdialog.h"
#include <QDebug>

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

void EditDialog::on_buttonBox_accepted()
{
    qDebug() << "on_buttonBox_accepted";
}

void EditDialog::on_buttonBox_rejected()
{
    qDebug() << "on_buttonBox_rejected";
}

void EditDialog::on_EditDialog_finished(int result)
{
    (void)result;
    qDebug() << "on_EditDialog_finished";
}

void EditDialog::on_plainTextEdit_textChanged()
{

}
