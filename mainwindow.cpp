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
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , glDrawer( new CGLDrawer(0) )
{
    ui->setupUi(this);


    mMenuList = new QMenu(this);

    editAction = mMenuList->addAction("Edit");
    addAction = mMenuList->addAction("Add");
    deleteAction = mMenuList->addAction("Delete");

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

    //connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(changeInfoTable()));
    //connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    //connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(currentRowChanged()));
    connect(ui->listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
    glDrawer->show();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete glDrawer;

}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
//    for(uint i(0); i < ui->listWidget->count(); i++)
//        if(ui->listWidget->isItemSelected(ui->listWidget->item(i)))
//        {
//            if( mMenuList)
//            {
//                editAction->setVisible(1);
//            }
//        }
    qDebug() << ui->listWidget->currentItem();
    if ( ui->listWidget->currentRow() == -1)
    {
        editAction->setEnabled(false);
        deleteAction->setEnabled(false);
    }
    else
    {
        editAction->setEnabled(true);
        deleteAction->setEnabled(true);
    }


    if(event->y() < ui->listWidget->geometry().height() && event->x() < ui->listWidget->geometry().width())
    {
        mMenuList->exec(event->globalPos());
    }


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

void MainWindow::changeInfoTable()
{

    if (ui->listWidget->count() == 0 )
    {
        for (int i=0; i<6; i++)
            item[i].setText("");
        glDrawer->setDrawData(DrawData());
        return;
    }

    QListWidgetItem * ci = ui->listWidget->currentItem();
    if (ci == nullptr)
        return;

    QString nameFigure = ci->text();

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

    glDrawer->setDrawData(listFigure(index)->getDrawData());


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
    listFigure(index) = testing;

    ui->listWidget->currentItem()->setText(QString::fromStdString(listFigure(index)->getName()));

    changeInfoTable();

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

    QListWidgetItem * li = new QListWidgetItem(QString::fromStdString(listFigure(index)->getName()),ui->listWidget);
    ui->listWidget->setCurrentItem(li);

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

    QListWidgetItem * ci = ui->listWidget->currentItem();

    if (ci != nullptr)
    {
        ci->setSelected(false);
        delete ci;
    }

    if (ui->listWidget->count() > 0 )
    {
        ui->listWidget->setCurrentItem(ui->listWidget->item(0));
    }
    else
    {
        changeInfoTable();
    }
}

void MainWindow::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() << "currentItemChanged";
    changeInfoTable();
}

void MainWindow::currentRowChanged(int index)
{
    qDebug() << "currentRowChanged";
    changeInfoTable();
}

void MainWindow::itemSelectionChanged()
{
    qDebug() << "itemSelectionChanged";
    changeInfoTable();
}

void MainWindow::on_actionOpen_triggered()
{
    CFigureParser pars(QFileDialog::getOpenFileName(this, "Open json files", ".//", "*.json").toStdString());

    if(pars.getNameFile()=="") return;

    std::shared_ptr<CFigure> figure = pars.getObject();

    if (figure.get() == nullptr)
    {
        ui->statusBar->showMessage("File \"" + QString::fromStdString(pars.getNameFile()) + "\" isn't correct");
        return;
    }

    if(figure->type() != CComplexFigure().type())
    {
        ui->statusBar->showMessage("It isn't list of figures");
        return ;
    }

    for(uint i(listFigure.countFigures()); i>0; i--)
        listFigure.deleteFigure(i);

    CComplexFigure * cf = (CComplexFigure *)figure.get();
    for(uint i(0); i < cf->countFigures(); i++)
        listFigure.addFigure((*cf)(i));

    ui->listWidget->clear();
    for(uint i(0); i<listFigure.countFigures(); i++)
        ui->listWidget->addItem(QString::fromStdString(listFigure(i)->getName()));

    ui->listWidget->setCurrentItem(ui->listWidget->item(0));

    ui->statusBar->showMessage("List of figures was added");
}
static const QString ext(".json");
void MainWindow::on_actionSave_triggered()
{

    QString file = QFileDialog::getSaveFileName(this, "Save figures into file", ".//", "*"+ext).trimmed();
    if (file.right(ext.length()).toLower() != ext)
    {
        file += ext;
    }

    CFigureParser pars(file.toStdString());

    if(!pars.save(listFigure.toJSON()))
    {
        ui->statusBar->showMessage("List of figures wasn't saved");
    }
    else
    {
        ui->statusBar->showMessage("List of figures was saved");
    }
}

void MainWindow::closeEvent(QCloseEvent *ev)
{
    glDrawer->close();
}

void MainWindow::showEvent(QShowEvent *ev)
{
    //QPoint pos = this->pos();
    //QSize size = this->size();
    QScreen * screen =  glDrawer->screen();
    screen->size();
    this->move(0,0);
    this->resize(500,2*screen->size().height()/3);
    glDrawer->resize(screen->size().width()/2-100,2*screen->size().height()/3);
    glDrawer->setPosition(this->pos().y()+this->size().width()+15,this->pos().x()+30);

}
