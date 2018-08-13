#include "seturncentralwidget.h"
#include <QMdiArea>

SeturnCentralWidget::SeturnCentralWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    m_mdiArea = new QMdiArea();
    layout->addWidget(m_mdiArea);
//    layout->setMargin(0);
    setLayout(layout);
}
