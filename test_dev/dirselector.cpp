#include "dirselector.h"
#include <QVBoxLayout>

DirSelector::DirSelector(QWidget *parent) : QWidget(parent)
{
    dirTreeView = new QTreeView;
    fileSystmeModel = new QFileSystemModel;
    fileSystmeModel->setRootPath("");
    fileSystmeModel->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Drives);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(dirTreeView);
    layout->addWidget(fileSystmeModel);

    setLayout(layout);

}
