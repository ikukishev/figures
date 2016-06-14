#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ccomplexfigure.h"
#include <QTableWidgetItem>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void contextMenuEvent(QContextMenuEvent *event);
public slots:

    void changeInfoTable();
    void editFigureDialog();
    void addFigureDialog();
    void deleteFigureAction();
private slots:
    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    CComplexFigure listFigure;
    QTableWidgetItem item[6];

    QAction* editAction;
    QMenu *mMenuList;
    bool itemListPressed;
};

#endif // MAINWINDOW_H
