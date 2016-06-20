#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cgldrawer.h"
#include "ccomplexfigure.h"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMenu>
#include <QListWidgetItem>


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
    void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void currentRowChanged(int index);
    void itemSelectionChanged();

private slots:
    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

protected:
    virtual void closeEvent(QCloseEvent * ev);
    virtual void showEvent(QShowEvent * ev);
private:
    Ui::MainWindow *ui;
    CComplexFigure listFigure;
    QTableWidgetItem item[6];
    CGLDrawer *glDrawer;


    QAction* editAction;
    QAction* addAction;
    QAction* deleteAction;
    QMenu *mMenuList;
    bool itemListPressed;
};

#endif // MAINWINDOW_H
