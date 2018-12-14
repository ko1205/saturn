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
    dirTreeView->hideColumn(1);
    dirTreeView->hideColumn(2);
    dirTreeView->hideColumn(3);

    searchButton = new QPushButton("Search Sequence");
    cancelButton = new QPushButton("Search Cancel");
    cancelButton->setEnabled(false);

    QHBoxLayout *buttonlayout = new QHBoxLayout;
    buttonlayout->setMargin(0);
    buttonlayout->addWidget(searchButton);
    buttonlayout->addWidget(cancelButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(dirTreeView);
//    layout->addWidget(selectorButton);
    layout->addLayout(buttonlayout);

    setLayout(layout);

    connect(dirTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(setCurrnetPaht(QModelIndex)));
    connect(searchButton,SIGNAL(clicked(bool)),this,SLOT(setEnableCancelButton(bool)));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SIGNAL(clickedCancelButton(bool)));
}

void DirSelector::setCurrnetPaht(QModelIndex index)
{
   currentPath =  fileSystemModel->filePath(index);
#ifdef QT_DEBUG
   qDebug() << currentPath;
#endif
}

void DirSelector::setEnableCancelButton(bool isClicked)
{
    if(!isClicked)
    {
        if (fileSystemModel->filePath(dirTreeView->currentIndex()) != currentPath)
        {
            return;
        }else{
            searchButton->setDisabled(true);
            cancelButton->setEnabled(true);
            emit clickedSearchButton(currentPath);
#ifdef QT_DEBUG
        qDebug() << currentPath;
#endif
        }
    }else{
        searchButton->setDisabled(false);
        cancelButton->setEnabled(false);
    }
}
