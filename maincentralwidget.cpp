#include "maincentralwidget.h"
#include <QMdiArea>
#include <QHBoxLayout>
#include "subwindow.h"

MainCentralWidget::MainCentralWidget(QWidget *parent) : QWidget(parent)
{
    createLayout();
    creatSubWindow();
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
}

void MainCentralWidget::creatSubWindow()
{
    QWidget *subwindow = new SubWindow;
    m_mdiArea->addSubWindow(subwindow);
    subwindow->showMaximized();
}

