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
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plateMainView);
    setLayout(layout);

}
