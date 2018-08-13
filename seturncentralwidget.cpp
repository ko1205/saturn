#include "seturncentralwidget.h"
#include <QMdiArea>
#include <QHBoxLayout>

SeturnCentralWidget::SeturnCentralWidget(QWidget *parent) : QWidget(parent)
{
    createLayout();
    creatSubWindow();
}

void SeturnCentralWidget::createLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();
    m_mdiArea = new QMdiArea();
    QWidget *temp = new QWidget;
    temp->setBaseSize(300,500);
    layout->addWidget(m_mdiArea);
    layout->addWidget(temp);
//    layout->setMargin(0);
    setLayout(layout);
}

void SeturnCentralWidget::creatSubWindow()
{
    QWidget *subwindow = new QWidget;
    m_mdiArea->addSubWindow(subwindow);
    subwindow->showMaximized();
}

