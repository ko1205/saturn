#include "plateviewcontroller.h"
#include "plateitemmodel.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QHeaderView>

PlateViewController::PlateViewController(QWidget *parent) : QWidget(parent)
{
    plateSequenceView = new QTableView();
    model = new PlateItemModel();

    plateSequenceView->setModel(model);
    QHeaderView *headerView = plateSequenceView->verticalHeader();
    headerView->setDefaultSectionSize(150);


    QPushButton *upButton = new QPushButton("Up");
    QPushButton *downButton = new QPushButton("Down");
    QPushButton *clearButton = new QPushButton("Clear");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin(0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(upButton);
    buttonLayout->addWidget(downButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(clearButton);

    QVBoxLayout *layout = new QVBoxLayout();

    layout->setMargin(0);
    layout->addWidget(plateSequenceView);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    resize(800,500);

    connect(clearButton,SIGNAL(clicked()),model,SLOT(clear()));

}

void PlateViewController::findedSequence(PlateItem item)
{
#ifdef QT_DEBUG
    qDebug()<<"find emit" << item.fileName;
#endif
//    PlateItem item;
    model->appendRow(item);
}


