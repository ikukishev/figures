#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "editdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog ad(this);
    ad.exec();
    EditDialog ed(this);
    ed.exec();

}
