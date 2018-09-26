#include "subwindow.h"
#include "platemainview.h"
#include "platedatamodel.h"
#include "platedelegate.h"
#include <QVBoxLayout>

SubWindow::SubWindow(QWidget *parent) : QWidget(parent)
{
    initWindow();
}

void SubWindow::initWindow()
{
    plateDataModel = new PlateDataModel;
    plateMainView = new PlateMainView;
    plateDelegate = new PlateDelegate;
    plateMainView->setItemDelegate(plateDelegate);

    plateMainView->setModel(plateDataModel);
    plateMainView->setSelectionBehavior(QAbstractItemView::SelectRows);
    plateMainView->setDragDropMode(QAbstractItemView::DragDrop);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plateMainView);
    setLayout(layout);
}
