#include "dirsettingtab.h"
#include <QSplitter>
#include <QGridLayout>
#include <QStandardItemModel>

DirSettingTab::DirSettingTab(QWidget *parent) : QWidget(parent)
{
    QStandardItemModel *templateModel = new QStandardItemModel;

    templateView = new QTreeView;
    preView = new QTreeView;
    propertyView = new QWidget;

    templateModel->setHorizontalHeaderLabels(QStringList("TemplateView"));
    templateView->setModel(templateModel);

    templateModel->appendRow(new QStandardItem("/"));

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(templateView);
    splitter->addWidget(preView);

    QGridLayout *layout = new QGridLayout;
    layout->setMargin(0);

    layout->addWidget(splitter,0,0);
    layout->addWidget(propertyView,0,1);

    setLayout(layout);

}
