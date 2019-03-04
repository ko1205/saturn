#include "platesequenceview.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>

PlateSequenceView::PlateSequenceView(QWidget *parent)
    :QTableView (parent)
{
    mulitValueAct = new QAction("rowNum");

    connect(mulitValueAct,SIGNAL(triggered(bool)),this,SLOT(testFunc()));

}

void PlateSequenceView::contextMenuEvent(QContextMenuEvent *event)
{
    contextPos = event->y();
    QMenu *popupMenu = new QMenu(this);
    popupMenu->addMenu("test");
    popupMenu->addAction(mulitValueAct);
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
