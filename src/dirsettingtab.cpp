#include "dirsettingtab.h"
#include <QSplitter>
#include <QGridLayout>
#include <QStandardItemModel>

#include <QLabel>
#include <QLineEdit>
//#include <QComboBox>
#include <QDebug>

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

    QLabel *startNum = new QLabel("Start Number :");
    QLabel *digitCount = new QLabel("Digit Number :");
    startNumEdit = new QSpinBox;
    startNumEdit->setMinimum(0);
    startNumEdit->setMaximum(99999999);

    digitNumEdit = new QSpinBox;
    digitNumEdit->setMinimum(1);
    digitNumEdit->setMaximum(8);


    QGridLayout *renumberLayout = new QGridLayout;
    renumberLayout->addWidget(startNum,0,0,1,2);
    renumberLayout->addWidget(digitCount,1,0,1,2);
    renumberLayout->addWidget(startNumEdit,0,2);
    renumberLayout->addWidget(digitNumEdit,1,2);
    renumberLayout->setRowStretch(2,1);

    renumberGrp = new QGroupBox("Set Number");
    renumberGrp->setCheckable(true);
    renumberGrp->setLayout(renumberLayout);

    QGridLayout *layoutTmp = new QGridLayout;
    layoutTmp->addWidget(label,0,0);
    layoutTmp->addWidget(lineEdit,0,1);
    layoutTmp->addWidget(type,1,0);
    layoutTmp->addWidget(typeCombo,1,1);
    layoutTmp->addWidget(renumberGrp,2,0,2,0);

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
    connect(renumberGrp,SIGNAL(clicked(bool)),this,SLOT(setRenumber(bool)));
    connect(startNumEdit,SIGNAL(valueChanged(int)),this,SLOT(setStartNum(int)));
    connect(digitNumEdit,SIGNAL(valueChanged(int)),this,SLOT(setDigitNum(int)));

}

void DirSettingTab::setPlateLIstModel(QAbstractItemModel *model)
{
    preView->setPlateListModel(model);
}

void DirSettingTab::connectItem(QStandardItem *item)
{
    currentItem = item;
    int type = item->data(Qt::UserRole).toInt();
    bool isRenumber = item->data(Qt::UserRole+3).toBool();
    int digitValue = item->data(Qt::UserRole+1).toInt();
    int startNumValue = item->data(Qt::UserRole+2).toInt();


    switch (type) {
    case 0:
        propertyView->setDisabled(true);
        break;
    case 1:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(0);
        renumberGrp->setDisabled(false);
        renumberGrp->setChecked(isRenumber);
        startNumEdit->setValue(startNumValue);
        digitNumEdit->setValue(digitValue);
        break;
    case 2:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(1);
        renumberGrp->setDisabled(true);
        renumberGrp->setChecked(isRenumber);
        startNumEdit->setValue(startNumValue);
        digitNumEdit->setValue(digitValue);
        break;
    case 3:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(2);
        renumberGrp->setDisabled(false);
        renumberGrp->setChecked(isRenumber);
        startNumEdit->setValue(startNumValue);
        digitNumEdit->setValue(digitValue);
        break;
    case 4:
        propertyView->setDisabled(false);
        typeCombo->setCurrentIndex(3);
        renumberGrp->setDisabled(true);
        renumberGrp->setChecked(isRenumber);
        startNumEdit->setValue(startNumValue);
        digitNumEdit->setValue(digitValue);
        break;

    default:
        break;
    }
}

void DirSettingTab::changeType(int index)
{
    currentItem->setData(index+1,Qt::UserRole);
    bool isRenumber = currentItem->data(Qt::UserRole+3).toBool();
//    disconnect(renumberGrp,SIGNAL(clicked(bool)),this,SLOT(setRenumber(bool)));
    switch (index) {
    case 0:
        renumberGrp->setDisabled(false);
        break;
    case 1:
        renumberGrp->setDisabled(true);
        break;
    case 2:
        renumberGrp->setDisabled(false);
        break;
    case 3:
        renumberGrp->setDisabled(true);
        break;
    default:
        break;
    }
}

void DirSettingTab::setRenumber(bool check)
{
    currentItem->setData(check,Qt::UserRole+3);
//    if(check)
//    {
//        qDebug() << "true";
//    }else{
//        qDebug() << "false";
//    }
}

void DirSettingTab::setStartNum(int value)
{
    currentItem->setData(value,Qt::UserRole+2);
}

void DirSettingTab::setDigitNum(int value)
{
    currentItem->setData(value,Qt::UserRole+1);
}

QStandardItemModel *DirSettingTab::getTemplateModel()
{
    return qobject_cast<QStandardItemModel*>(templateView->model());
}

TemplateView *DirSettingTab::getTemplateView()
{
    return templateView;
}
