#include "plateviewcontroller.h"
#include "plateitemmodel.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

PlateViewController::PlateViewController(QWidget *parent) : QWidget(parent)
{
    plateSequenceView = new QTableView();
    model = new PlateItemModel();

    plateSequenceView->setModel(model);

    QPushButton *upButton = new QPushButton("Up");
    QPushButton *downButton = new QPushButton("Down");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(upButton);
    buttonLayout->addWidget(downButton);
    buttonLayout->addStretch();

    QVBoxLayout *layout = new QVBoxLayout();

    layout->setMargin(0);
    layout->addWidget(plateSequenceView);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    resize(800,500);

}

void PlateViewController::findedSequence(QString path)
{
#ifdef QT_DEBUG
    qDebug()<<"find emit" << path;
#endif
    PlateItem item;
    model->appendRow(item);
}
