#include "maincentralwidget.h"
#include <QMdiArea>
#include <QHBoxLayout>
#include "subwindow.h"

MainCentralWidget::MainCentralWidget(QWidget *parent) : QWidget(parent)
{
    createLayout();
    newProject();   //임시용
}

void MainCentralWidget::createLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();
    m_mdiArea = new QMdiArea();
    QWidget *temp = new QWidget;
    temp->setBaseSize(300,500);
    layout->addWidget(m_mdiArea);
    layout->addWidget(temp);
    layout->setMargin(0);
    setLayout(layout);

//    connect(m_mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT());  // test code
}

SubWindow *MainCentralWidget::creatSubWindow()
{
    SubWindow *subwindow = new SubWindow;
    m_mdiArea->addSubWindow(subwindow);
    return subwindow;
}

void MainCentralWidget::newProject()
{
    currentSubwindow = creatSubWindow();
    currentSubwindow->showMaximized();
    currentSubwindow->setWindowTitle(tr("test[*]"));
    currentSubwindow->setWindowModified(true);

}
