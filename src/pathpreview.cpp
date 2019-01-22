#include "pathpreview.h"
#include <QMessageBox>
#include <QDebug>

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

void PathPreView::setPlateListModel(QAbstractItemModel *model)
{
    plateListModel = model;
}

QStandardItem *PathPreView::readTemplateViewLoop(QModelIndex &index,QModelIndex &previewIndex,QStandardItem *parentItem, int deepth)
{
/*
    QStandardItem *item;
    bool hasChildren = templateModel->hasChildren(index);
    if(hasChildren)
    {
        int childrenCount = templateModel->rowCount(index);
        for(int i = 0; i< childrenCount; i++)
        {
            QModelIndex childIndex = templateModel->index(i,0,index);
            QString childData = templateModel->data(childIndex).toString();
            bool childIsFolder = templateModel->data(childIndex,Qt::UserRole).toBool();
            if(!parentItem){

                item = new QStandardItem(folderIcon,childData);
            }
        }
    }
    return item;
*/

//    preViewModel->removeRow(0,rootIndex());
//    QModelIndex templateIndex = templateModel->index(0,0);
//    QStandardItem *TemplateRootItem = templateModel->itemFromIndex(index);

    /*
     * 다시 작성
     */


}



void PathPreView::updatePrevew()
{
    QStandardItem *item;
    int rowCount = plateListModel->rowCount();
    if(rowCount != 0){
        QModelIndex previewIndex = rootIndex();
        preViewModel->removeRow(0,previewIndex);
        QStandardItem *templateRootItem = templateModel->item(0);
        QStandardItem *preViewRoot = new QStandardItem(templateRootItem->data(Qt::DisplayRole).toString());
//        templateModel->inde
        for(int i = 0; i < rowCount; i++)
        {
            QModelIndex index;
//            preViewModel->appendRow(readTemplateViewLoop(index,previewIndex,tempItem));
            item = testFunc(i,templateModel->item(0));

        }
//        preViewModel->appendRow(item);
    }
//    qDebug() << rowCount;
//    QString tmp = replaceName("test[shot]_test");
//    qDebug() << templateModel->hasChildren(QModelIndex());
//    qDebug() << templateModel->rowCount(QModelIndex());
//    qDebug() << templateModel->rowCount(templateModel->index(0,0));
}

QString PathPreView::replaceName(QString Name,int num)
{
    QModelIndex sceneIndex = plateListModel->index(num,4);
    QString sceneData = plateListModel->data(sceneIndex).toString();
    Name.replace("[scene]",sceneData);

    QModelIndex shotIndex = plateListModel->index(num,5);
    QString shotData = plateListModel->data(shotIndex).toString();
    Name.replace("[shot]",shotData);

    return Name;
}

QStandardItem *PathPreView::testFunc(int num,QStandardItem *templateItem,QStandardItem *preViewParentItem)
{
    bool hasSameItem = false;
    QStandardItem *item;
    int previewRowCount;
    QString templatName = templateItem->data(Qt::DisplayRole).toString();
    int templateIsFolder = templateItem->data(Qt::UserRole).toInt();
    templatName = replaceName(templatName,num);
    if(preViewParentItem)
    {
        previewRowCount = preViewParentItem->rowCount();
        for(int i = 0;i<previewRowCount;i++)
        {
            QStandardItem *child =  preViewParentItem->child(i);
            QString childName = child->data(Qt::DisplayRole).toString();
            int childIsFolder = child->data(Qt::UserRole).toInt();
            if(templatName == childName && templateIsFolder == childIsFolder)
            {
                hasSameItem = true;
                item = child;
            }
        }

    }else{
        previewRowCount = preViewModel->rowCount();
        for(int i = 0;i<previewRowCount;i++)
        {
            QModelIndex index = preViewModel->index(i,0);
            QStandardItem *child =  preViewModel->itemFromIndex(index);
            QString childName = child->data(Qt::DisplayRole).toString();
            int childIsFolder = child->data(Qt::UserRole).toInt();
            if(templatName == childName && templateIsFolder == childIsFolder)
            {
                hasSameItem = true;
                item = child;
            }
        }
    }
    if(!hasSameItem)
    {
        if(!templateIsFolder)
        {
            item = new QStandardItem(folderIcon,templatName);
            item->setData(0,Qt::UserRole);
        }else{
            item = new QStandardItem(fileIcon,templatName);
            item->setData(1,Qt::UserRole);
        }

        if(preViewParentItem)
        {
            preViewParentItem->appendRow(item);
            expandAll();
        }else{
            preViewModel->appendRow(item);
            expandAll();
        }
    }
    if(!templateIsFolder)
    {
        int templateChildCount = templateItem->rowCount();
        if(templateChildCount != 0)
        {
            for(int i = 0;i<templateChildCount; i++)
            {
                testFunc(num,templateItem->child(i),item);
            }
        }

    }
    return item;
}
