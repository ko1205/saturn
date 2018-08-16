#include "mainwindow.h"
#include <QStatusBar>
#include <QMenuBar>
#include "maincentralwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenuBar();

    m_centralWidget = new MainCentralWidget;
    setCentralWidget(m_centralWidget);

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
