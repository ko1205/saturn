#include "dirsettingtab.h"
#include <QSplitter>
#include <QGridLayout>
#include <QStandardItemModel>

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

DirSettingTab::DirSettingTab(QWidget *parent) : QWidget(parent)
{
    templateView = new TemplateView;
    preView = new PathPreView;
    propertyView = new QWidget;

    preView->setTemplateModel(templateView->model());

    QLabel *label = new QLabel("Name : ");
    QLineEdit *lineEdit = new QLineEdit();

    QLabel *type = new QLabel("Type : ");
    QComboBox *typeCombo =new QComboBox;
    typeCombo->addItem("File Copy");
    typeCombo->addItem("Thumbnail");
    typeCombo->addItem("Jpeg proxy");
    typeCombo->addItem("PreView Mov");

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

}
