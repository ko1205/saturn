#include "templateview.h"

TemplateView::TemplateView(QWidget *parent)
    :QTreeView(parent)
{
    templateModel = new QStandardItemModel;

    templateModel->setHorizontalHeaderLabels(QStringList("TemplateView"));

    createIcon();
    createRootFolder();

    setModel(templateModel);

    popupMenu = new QMenu(this);
    insertFolderAct = new QAction("Create Folder",this);

    popupMenu->addAction(insertFolderAct);

    connect(insertFolderAct,SIGNAL(triggered(bool)),this,SLOT(insertFolder()));

}

void TemplateView::createIcon()
{

    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),QIcon::Normal,QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),QIcon::Normal,QIcon::On);
    fileIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon),QIcon::Normal,QIcon::On);

}

void TemplateView::createRootFolder()
{
    rootItem = new QStandardItem("/");
    rootItem->setIcon(folderIcon);
    templateModel->appendRow(rootItem);
    rootItem->setEditable(false);

}

void TemplateView::contextMenuEvent(QContextMenuEvent *event)
{
    popupMenu->exec(event->globalPos());
}

void TemplateView::insertFolder()
{
    QModelIndex index = currentIndex();
    QStandardItem *newFolder = new QStandardItem("test_Folder");
    newFolder->setIcon(folderIcon);
//    index == rootIndex() ||
    templateModel->itemFromIndex(index)->appendRow(newFolder);

}

void TemplateView::deleteFolder()
{

}

void TemplateView::setRootFolderName()
{

}
