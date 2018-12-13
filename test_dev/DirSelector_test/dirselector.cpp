#include "dirselector.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

DirSelector::DirSelector(QWidget *parent) : QWidget(parent)
{
    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath("");
    fileSystemModel->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Drives);

    dirTreeView = new QTreeView;
    dirTreeView->setModel(fileSystemModel);

    selectorButton = new QPushButton("Search Sequence");
    cancelButton = new QPushButton("Cancel");

    QHBoxLayout *buttonlayout = new QHBoxLayout;
    buttonlayout->setMargin(0);
    buttonlayout->addWidget(selectorButton);
    buttonlayout->addWidget(cancelButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(dirTreeView);
//    layout->addWidget(selectorButton);
    layout->addLayout(buttonlayout);

    setLayout(layout);

    connect(dirTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(setCurrnetPaht(QModelIndex)));
}

void DirSelector::setCurrnetPaht(QModelIndex index)
{
   currentPath =  fileSystemModel->filePath(index);
#ifdef QT_DEBUG
   qDebug() << currentPath;
#endif
}
