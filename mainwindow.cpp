#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "editdialog.h"
#include "cfigureparser.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <cfigure.h>
#include <ccomplexfigure.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mMenuList = new QMenu(this);

    editAction = mMenuList->addAction("Edit");
    QAction* addAction = mMenuList->addAction("Add");
    QAction* deleteAction = mMenuList->addAction("Delete");
    editAction->setVisible(0);
    connect(editAction, SIGNAL(triggered() ), this, SLOT(editFigureDialog()));
    connect(addAction, SIGNAL(triggered() ), this, SLOT(addFigureDialog()));
    connect(deleteAction, SIGNAL(triggered() ), this, SLOT(deleteFigureAction()));

    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(1);

    for(int i(0); i<6; i++){
            item[i].setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,0,&item[i]);
    }

    QStringList listHeaders, lh;

    listHeaders.insert(0, "type");
    listHeaders.insert(1, "edges");
    listHeaders.insert(2, "facets");
    listHeaders.insert(3, "vertex");
    listHeaders.insert(4, "volume");
    listHeaders.insert(5, "surface area");

    lh.insert(1, "property value");

    ui->tableWidget->setVerticalHeaderLabels(listHeaders);
    ui->tableWidget->setHorizontalHeaderLabels(lh);
    //ui->tableWidget->set

    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeInfoTable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    for(uint i(0); i<ui->listWidget->count(); i++)
    if(ui->listWidget->isItemSelected(ui->listWidget->item(i)))
    {
        if( mMenuList)
        {
            editAction->setVisible(1);
        }
    }
    mMenuList->exec(event->globalPos());
    editAction->setVisible(0);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog ad(this);

    ad.exec();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::contextMenuFigure()
{

}

void MainWindow::changeInfoTable()
{
    QString nameFigure = ui->listWidget->currentItem()->text();

    int index=-1;
    for(uint i(0); i<listFigure.countFigures();i++)
        if(listFigure(i)->getName() == nameFigure.toStdString())
        {
            index=i;
        }

    if(index == -1)
        return;

        item[0].setText(QString::fromStdString(listFigure(index)->type()));
        item[1].setText(QString::number(listFigure(index)->countEdge()));
        item[2].setText(QString::number(listFigure(index)->countFacets()));
        item[3].setText(QString::number(listFigure(index)->countVertex()));
        item[4].setText(QString::number(listFigure(index)->volume()));
        item[5].setText(QString::number(listFigure(index)->surfaceArea()));

//    for(int i(0); i<6; i++){
//            item[i].setTextAlignment(Qt::AlignCenter);
//            ui->tableWidget->setItem(0,i,&item[i]);
//    }
//    //QMessageBox::information(this, "test", "test");
        //ui->tableWidget->repaint();
}

void MainWindow::editFigureDialog()
{
    EditDialog ed(this);

    QString nameFigure = ui->listWidget->currentItem()->text();

    int index=-1;
    for(uint i(0); i<listFigure.countFigures();i++)
        if(listFigure(i)->getName() == nameFigure.toStdString())
        {
            index=i;
        }

    if(index == -1)
        return;

    ed.setFigureObject(listFigure(index)->toJSON());
    ed.exec();

    std::shared_ptr<CFigure> testing=ed.getObjectFigure();

    if(testing == nullptr) return;

    ui->listWidget->currentItem()->setText(QString::fromStdString(listFigure(index)->getName()));

    item[0].setText(QString::fromStdString(listFigure(index)->type()));
    item[1].setText(QString::number(listFigure(index)->countEdge()));
    item[2].setText(QString::number(listFigure(index)->countFacets()));
    item[3].setText(QString::number(listFigure(index)->countVertex()));
    item[4].setText(QString::number(listFigure(index)->volume()));
    item[5].setText(QString::number(listFigure(index)->surfaceArea()));

    //ui->listWidget->addItem(QString::fromStdString(listFigure(listFigure.countFigures()-1)->getName()));

}

void MainWindow::addFigureDialog()
{
    EditDialog ed(this);

    ed.exec();

    std::shared_ptr<CFigure> testing=ed.getObjectFigure();
    if(testing == nullptr) return;

    if(!listFigure.addFigure(testing))
    {

        ui->statusBar->showMessage("There is Figure with name "+QString::fromStdString(ed.getObjectFigure()->getName())+" already is");
        return;
    }

    uint index = listFigure.countFigures()-1;

    ui->listWidget->addItem(QString::fromStdString(listFigure(index)->getName()));

    item[0].setText(QString::fromStdString(listFigure(index)->type()));
    item[1].setText(QString::number(listFigure(index)->countEdge()));
    item[2].setText(QString::number(listFigure(index)->countFacets()));
    item[3].setText(QString::number(listFigure(index)->countVertex()));
    item[4].setText(QString::number(listFigure(index)->volume()));
    item[5].setText(QString::number(listFigure(index)->surfaceArea()));

    ui->statusBar->showMessage("Figure was added");
}

void MainWindow::deleteFigureAction()
{
    QString nameFigure = ui->listWidget->currentItem()->text();

    int index=-1;
    for(uint i(0); i<listFigure.countFigures();i++)
        if(listFigure(i)->getName() == nameFigure.toStdString())
        {
            index=i;
        }

    if(index == -1)
        return;

    listFigure.deleteFigure(index);

    delete ui->listWidget->currentItem();
}

void MainWindow::on_actionOpen_triggered()
{
    CFigureParser pars(QFileDialog::getOpenFileName(this, "Open json files", ".//", "*.json").toStdString());

    if(pars.getNameFile()=="") return;

    if(pars.getObject()->type() != CComplexFigure().type())
    {
        ui->statusBar->showMessage("It isn't list of figures");
        return ;
    }

    for(uint i(listFigure.countFigures()); i>0; i--)
    listFigure.deleteFigure(i);

    for(uint i(0); i<pars.getObject()->countFigures(); i++)
    listFigure.addFigure(pars.getObject()->operator ()(i));

    ui->listWidget->clear();
    for(uint i(0); i<listFigure.countFigures(); i++)
    ui->listWidget->addItem(QString::fromStdString(listFigure(i)->getName()));

    ui->statusBar->showMessage("List of figures was added");
}

void MainWindow::on_actionSave_triggered()
{
    CFigureParser pars(QFileDialog::getSaveFileName(this, "Save figures into file", ".//", "*.json").toStdString());

    if(!pars.save(listFigure.toJSON()))
    {
        return;
        ui->statusBar->showMessage("List of figures wasn't saved");
    }

    ui->statusBar->showMessage("List of figures was saved);
}
