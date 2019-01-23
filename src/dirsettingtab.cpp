#include "dirsettingtab.h"
#include <QSplitter>
#include <QGridLayout>
#include <QStandardItemModel>

#include <QLabel>
#include <QLineEdit>
//#include <QComboBox>

DirSettingTab::DirSettingTab(QWidget *parent) : QWidget(parent)
{
    templateView = new TemplateView;
    preView = new PathPreView;
    propertyView = new QWidget;

    preView->setTemplateModel(templateView->model());
    templateView->setPathPreview(preView);

    QLabel *label = new QLabel("Name : ");
    QLineEdit *lineEdit = new QLineEdit();

    QLabel *type = new QLabel("Type : ");
    typeCombo =new QComboBox;
//    typeCombo->addItem("folder");
    typeCombo->addItem("File Copy");
    typeCombo->addItem("Thumbnail");
    typeCombo->addItem("Jpeg proxy");
    typeCombo->addItem("Preview Mov");

    QGridLayout *layoutTmp = new QGridLayout;
    layoutTmp->addWidget(label,0,0);
    layoutTmp->addWidget(lineEdit,0,1);
    layoutTmp->addWidget(type,1,0);
    layoutTmp->addWidget(typeCombo,1,1);

    propertyView->setLayout(layoutTmp);

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(templateView);
    splitter->addWidget(preView);

    QGridLayout *layout = new QGridLayout;
    layout->setMargin(0);

    layout->addWidget(splitter,0,0);
    layout->addWidget(propertyView,0,1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,0);

    label->setVisible(false);
    lineEdit->setVisible(false);
    setLayout(layout);
    propertyView->setDisabled(true);

    connect(templateView,SIGNAL(itemClickedView(QStandardItem*)),this,SLOT(connectItem(QStandardItem*)));
    connect(typeCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(changeType(int)));

}

void DirSettingTab::setPlateLIstModel(QAbstractItemModel *model)
{
    preView->setPlateListModel(model);
}

void DirSettingTab::connectItem(QStandardItem *item)
{
    currentItem = item;
    int type = item->data(Qt::UserRole).toInt();

    switch (type) {
    case 0:
        propertyView->setDisabled(true);
        break;
    case 1:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(0);
        break;
    case 2:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(1);
        break;
    case 3:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(2);
        break;
    case 4:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(3);
        break;

    default:
        break;
    }
}

void DirSettingTab::changeType(int index)
{
    currentItem->setData(index+1,Qt::UserRole);
}
