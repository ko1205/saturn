#include "subwindow.h"
#include "platemainview.h"
#include "platedatamodel.h"
#include <QVBoxLayout>

SubWindow::SubWindow(QWidget *parent) : QWidget(parent)
{
    initWindow();
}

void SubWindow::initWindow()
{
    plateDataModel = new PlateDataModel;
    plateMainView = new PlateMainView;
    plateMainView->setModel(plateDataModel);

    plateMainView->resizeColumnsToContents();
    plateMainView->resizeRowsToContents();
//    plateMainView->setColumnWidth(0,500);

    plateMainView->setSelectionBehavior(QAbstractItemView::SelectRows);
    plateMainView->setDragDropMode(QAbstractItemView::DragDrop);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plateMainView);
    setLayout(layout);
}


