#include "plateviewcontroller.h"
#include "plateitemmodel.h"
#include "plateviewdelegate.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>

PlateViewController::PlateViewController(QWidget *parent) : QWidget(parent)
{
    plateSequenceView = new QTableView();
    oldScrollMax = 0;
    model = new PlateItemModel();
    PlateViewDelegate *delegate = new PlateViewDelegate;

    plateSequenceView->setModel(model);
    plateSequenceView->setItemDelegate(delegate);
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
    connect(plateSequenceView->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(rowResiz(int,int,int)));
    connect(plateSequenceView->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),this,SLOT(autoScroll(int,int)));

}

void PlateViewController::findedSequence(PlateItem item)
{
#ifdef QT_DEBUG
    qDebug()<<"find emit" << item.fileName;
#endif
//    PlateItem item;
    model->appendRow(item);
}

void PlateViewController::rowResiz(int index, int oldSize, int newSize)
{
    /*
     * rowSize 일괄변경 함수;
     */
    oldScrollMax = plateSequenceView->verticalScrollBar()->maximum();
    disconnect(plateSequenceView->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(rowResiz(int,int,int)));

    for(int i =0; i < model->rowCount(QModelIndex());i++){
    plateSequenceView->setRowHeight(i,newSize);
    }

    connect(plateSequenceView->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(rowResiz(int,int,int)));
}

void PlateViewController::autoScroll(int min, int max)
{
    int value = plateSequenceView->verticalScrollBar()->value();
    if(value!=0){
        float valuePerOldMax = (float)value/oldScrollMax;
        plateSequenceView->verticalScrollBar()->setValue(valuePerOldMax*max);
    }
    oldScrollMax = max;
}

QAbstractItemModel *PlateViewController::getModel()
{
    return model;
}
