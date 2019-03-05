#include "platesequenceview.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <QInputDialog>

PlateSequenceView::PlateSequenceView(QWidget *parent)
    :QTableView (parent)
{
    removeSelectedAct = new QAction("remove selected");
    itemUpAct = new QAction("Up");
    itemDownAct = new QAction("Down");
    singleDataInputAct = new QAction("Single Data Input");
    sequentialDataInputAct = new QAction("Sequential Data Input");

    connect(removeSelectedAct,SIGNAL(triggered(bool)),this,SLOT(removeSelected()));
    connect(itemUpAct,SIGNAL(triggered(bool)),this,SLOT(itemUp()));
    connect(itemDownAct,SIGNAL(triggered(bool)),this,SLOT(itemDown()));
    connect(singleDataInputAct,SIGNAL(triggered(bool)),this,SLOT(singleDataInput()));
    connect(sequentialDataInputAct,SIGNAL(triggered(bool)),this,SLOT(sequentialDataInput()));
}

void PlateSequenceView::contextMenuEvent(QContextMenuEvent *event)
{
    contextPos = event->y();
    QMenu *popupMenu = new QMenu(this);
    QMenu *inputMenu = popupMenu->addMenu("Multiple Data Input");
    popupMenu->addSeparator();
    popupMenu->addAction(itemUpAct);
    popupMenu->addAction(itemDownAct);
    popupMenu->addSeparator();
    popupMenu->addAction(removeSelectedAct);
    inputMenu->addAction(singleDataInputAct);
    inputMenu->addAction(sequentialDataInputAct);
    popupMenu->exec(event->globalPos());

}

void PlateSequenceView::testFunc()
{
    int index = rowAt(contextPos);
    QModelIndexList lists =  selectedIndexes();
    qDebug() << index;
    foreach (QModelIndex index, lists) {
        qDebug() << index.row() << " " << index.column();
    }
    model()->removeRow(index);
}

void PlateSequenceView::removeSelected()
{
    QModelIndexList list = selectedIndexes();
    while (!list.isEmpty()) {
        model()->removeRow(list[0].row());
        list = selectedIndexes();
    }
}

void PlateSequenceView::itemUp()
{
    int preItemIndex = 0;
    QModelIndexList list = selectedIndexes();
    qSort(list.begin(),list.end(),qLess<QModelIndex>());
    if(list[0].row() != 0){
        foreach (QModelIndex index, list) {
            if(index.row() != preItemIndex){
                model()->moveRow(QModelIndex(),index.row(),QModelIndex(),index.row()-1);
            }
            preItemIndex = index.row();
        }
    }
}

void PlateSequenceView::itemDown()
{
    int preItemIndex = 0;
    QModelIndexList list = selectedIndexes();
    qSort(list.begin(),list.end(),qGreater<QModelIndex>());
    if(list.first().row() != model()->rowCount()-1){
        foreach (QModelIndex index, list) {
            if(index.row() != preItemIndex){
                model()->moveRow(QModelIndex(),index.row(),QModelIndex(),index.row()+2);
            }
            preItemIndex = index.row();
        }
    }
}

void PlateSequenceView::singleDataInput()
{
    QModelIndexList list = selectedIndexes();
    bool ok;
    QString value = QInputDialog::getText(this,"Single Data Input", "Value",QLineEdit::Normal);

}

void PlateSequenceView::sequentialDataInput()
{

}


