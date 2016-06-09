#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_EditDialog_finished(int result);

    void on_plainTextEdit_textChanged();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
