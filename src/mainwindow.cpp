#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QInputDialog>
#include "centralwidget.h"
#include <QMessageBox>
#include <QDebug>

DeleteTemplateDialog::DeleteTemplateDialog(QWidget *parent)
    :QDialog(parent)
{

}

DeleteTemplateDialog::~DeleteTemplateDialog()
{

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    centralwidget = new CentralWidget;
    setCentralWidget(centralwidget);
    createAction();
    createMenus();

}


void MainWindow::createAction()
{
   saveTemplateAct = new QAction(tr("Save Template"),this);
   connect(saveTemplateAct,SIGNAL(triggered(bool)),this,SLOT(saveTemplate()));

   deleteTemplateAct = new QAction(tr("Delete Template"),this);
   connect(deleteTemplateAct,SIGNAL(triggered(bool)),this,SLOT(deleteTemplate()));

   importTemplateAct = new QAction(tr("Import Template"),this);
   connect(importTemplateAct,SIGNAL(triggered(bool)),this,SLOT(importTemplate()));

   exportTemplateAct = new QAction(tr("Export Template"),this);
   connect(exportTemplateAct,SIGNAL(triggered(bool)),this,SLOT(exportTemplate()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveTemplateAct);
    fileMenu->addAction(deleteTemplateAct);
    fileMenu->addSeparator();
    fileMenu->addAction(importTemplateAct);
    fileMenu->addAction(exportTemplateAct);
}

void MainWindow::saveTemplate()
{
    bool ok;
    QString templateName = QInputDialog::getText(this,"Save Template","TemplateName",QLineEdit::Normal,"template",&ok);
    if(ok && !templateName.isEmpty())
    {
        centralwidget->getTemplateControl()->saveTemplateList(templateName);
    }
}

void MainWindow::deleteTemplate()
{
    DeleteTemplateDialog deleteTemplateWindow(this);
    deleteTemplateWindow.exec();
    qDebug() << "deleteTemplate Test";

}

void MainWindow::importTemplate()
{

}

void MainWindow::exportTemplate()
{

}
