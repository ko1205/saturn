#include "pathpreview.h"

PathPreView::PathPreView(QWidget *parent)
    :QTreeView(parent)
{
    preViewModel = new QStandardItemModel;

    preViewModel->setHorizontalHeaderLabels(QStringList()<<"Name" << "Type");

    createIcon();
    createRootFolder();

    setModel(preViewModel);

}

void PathPreView::createIcon()
{
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),QIcon::Normal,QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),QIcon::Normal,QIcon::On);
    fileIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon),QIcon::Normal,QIcon::On);
}

void PathPreView::createRootFolder()
{
    rootItem = new QStandardItem("/");
    rootItem->setIcon(folderIcon);
    preViewModel->appendRow(rootItem);
}

void PathPreView::setTemplateModel(QAbstractItemModel *model)
{

    templateModel = qobject_cast<QStandardItemModel *>(model);
}

void PathPreView::readTemplateView()
{
    QModelIndex index = templateModel->index(0,0);
    QStandardItem *item = templateModel->itemFromIndex(index);
}
