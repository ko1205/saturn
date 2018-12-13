#include "dirselector.h"
#include <QVBoxLayout>

DirSelector::DirSelector(QWidget *parent) : QWidget(parent)
{
    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath("");
    fileSystemModel->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Drives);

    dirTreeView = new QTreeView;
    dirTreeView->setModel(fileSystemModel);

    selectorButton = new QPushButton("Search Sequence");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(dirTreeView);
    layout->addWidget(selectorButton);

    setLayout(layout);

}
