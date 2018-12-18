#include "plateviewcontroller.h"
#include "plateitemmodel.h"
#include <QHBoxLayout>
#include <QPushButton>

PlateViewController::PlateViewController(QWidget *parent) : QWidget(parent)
{
    plateSequenceView = new QTableView();
    PlateItemModel *model = new PlateItemModel();

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

}
