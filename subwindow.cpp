#include "subwindow.h"
#include "platemainview.h"
#include "platedatamodel.h"
#include "platedelegate.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "commonfunc.h"
#include <QDebug>

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

    plateMainView->resizeColumnsToContents();
    plateMainView->resizeRowsToContents();
//    plateMainView->setColumnWidth(0,500);

    /*
     * 아래 두줄 테스트코드
     */
//    QPushButton *testButton = new QPushButton("test");
//    plateMainView->setIndexWidget(plateDataModel->index(0,0),testButton);

    plateMainView->setSelectionBehavior(QAbstractItemView::SelectRows);
    plateMainView->setDragDropMode(QAbstractItemView::DragDrop);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plateMainView);
    setLayout(layout);
}

bool SubWindow::appendItem(sequenceInfo &item)
{
    plateDataModel->appendItem(item);
//    plateMainView->viewport()->update();
    qDebug() << "appended";
    plateMainView->resizeRowsToContents();
    return 0;
}
