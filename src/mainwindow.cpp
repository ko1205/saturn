#include "mainwindow.h"
#include <QVBoxLayout>
#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    CentralWidget *centralwidget = new CentralWidget;
    setCentralWidget(centralwidget);

}
