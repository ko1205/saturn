#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    CentralWidget *centralwidget = new CentralWidget;
    setCentralWidget(centralwidget);
    createAction();
    createMenus();

}


void MainWindow::createAction()
{
   saveTemplateAct = new QAction(tr("Save Template"),this);

   deleteTemplateAct = new QAction(tr("Save Template"),this);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveTemplateAct);
    fileMenu->addAction(deleteTemplateAct);
}
