#include "mainwindow.h"
#include <QStatusBar>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenuBar();
    statusBar()->showMessage("Started Saturn");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuBar()
{
    menuBar()->setNativeMenuBar(false);
    menuBar()->addMenu(tr("&File"));

}

void MainWindow::createAction()
{

}
