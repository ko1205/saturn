#include "mainwindow.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include "maincentralwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenuBar();
    createToolbar();

    m_centralWidget = new MainCentralWidget;
    setCentralWidget(m_centralWidget);

    setWindowModified(true);
    statusBar()->showMessage("Started Saturn");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);

    menuBar()->setNativeMenuBar(false);

    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(newProject()));
}

void MainWindow::createToolbar()
{
    fileToolbar = addToolBar(tr("file"));
    fileToolbar->addAction(newAct);
}

void MainWindow::createAction()
{
    newAct = new QAction(tr("New Project"));

}

bool MainWindow::newProject()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setDirectory(QDir::home());
    if(dialog.exec()){
        QStringList rootPaths = dialog.selectedFiles();
//        this->setCursor(Qt::WaitCursor);      //test code
        return m_centralWidget->newProject(rootPaths.at(0));
    }
    return false;
}
