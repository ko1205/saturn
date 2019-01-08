#include "templateview.h"

TemplateView::TemplateView(QWidget *parent)
    :QTreeView(parent)
{
    templateModel = new QStandardItemModel;

    templateModel->setHorizontalHeaderLabels(QStringList()<<"Name" << "Type");

    createIcon();
    createRootFolder();

    setModel(templateModel);

    popupMenu = new QMenu(this);
    insertFolderAct = new QAction("Create Folder",this);
    newFile = new QAction("Create File",this);

    popupMenu->addAction(insertFolderAct);
    popupMenu->addAction(newFile);

    connect(insertFolderAct,SIGNAL(triggered(bool)),this,SLOT(insertFolder()));
    connect(newFile,SIGNAL(triggered(bool)),this,SLOT(newFileSlot()));

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
    rootItem->setData(true,Qt::UserRole);
    rootItem->setIcon(folderIcon);
    templateModel->appendRow(QList<QStandardItem*>()<<rootItem << new QStandardItem("folder"));
    rootItem->setEditable(false);
}

void TemplateView::contextMenuEvent(QContextMenuEvent *event)
{
    popupMenu->exec(event->globalPos());
}

void TemplateView::insertFolder()
{
    QModelIndex index = currentIndex();
    /*
     * 선택된 Item이 폴더일 경우에만 children 생성
     * 폴더일떄 와 파일일때 함수구조가 같으므로 나중에 하나의 함수로 통합정리
     */
    if(!index.data(Qt::UserRole).toBool())
    {
        index = index.parent();
    }
    QString folderName = "NewFolder%1";
//    folderName.arg("test Code");
    QString sub = autoRename(folderName,true,index);
    QStandardItem *newFolder = new QStandardItem(folderName.arg(sub));
    newFolder->setData(true,Qt::UserRole);
    newFolder->setIcon(folderIcon);
    templateModel->itemFromIndex(index)->appendRow(QList<QStandardItem*>()<<newFolder << new QStandardItem("folder"));

    /*
     * 1차 nameing 순으로 정렬후 다시 타입 순으로 정렬 parent폴더 expand;
     * 아래 내용도 Item 추가 하거나 naming 또는 타입 변경시에도 호출이 필요하므로 함수 또는
     * SIGNAL로 변경 필요
     */
    rootItem->sortChildren(0);
    rootItem->sortChildren(1,Qt::DescendingOrder);
    expand(index);
}

void TemplateView::newFileSlot()
{
    QModelIndex index = currentIndex();
    if(!index.data(Qt::UserRole).toBool())
    {
        index = index.parent();
    }
    QStandardItem *newFile = new QStandardItem("newFilew");
    newFile->setData(false,Qt::UserRole);
    newFile->setIcon(fileIcon);
    templateModel->itemFromIndex(index)->appendRow(QList<QStandardItem*>()<<newFile << new QStandardItem("file"));
    rootItem->sortChildren(0);
    rootItem->sortChildren(1,Qt::DescendingOrder);
    expand(index);
}

void TemplateView::deleteFolder()
{

}

void TemplateView::setRootFolderName()
{

}

bool TemplateView::checkSameName(QString name,bool isFolder, const QModelIndex &parent)
{
    int rowCount = templateModel->rowCount(parent);
    for(int i=0;i<rowCount;i++)
    {
        QString rowName = parent.child(i,0).data().toString();
        bool rowIsFolder = parent.child(i,1).data().toBool();
       if(rowName.toUpper() == name.toUpper() && isFolder == rowIsFolder)
       {
           return true;
       }
    }
    return false;
}

QString TemplateView::autoRename(QString name, bool isFolder, const QModelIndex &parent,int count)
{
    if(count == 0){
        if(checkSameName(name.arg(""),isFolder,parent))
        {
            return autoRename(name,isFolder,parent,1);
        }else{
            return QString("");
        }
    }else{
        if(checkSameName(name.arg("("+QString::number(count)+")"),isFolder,parent))
        {
            return autoRename(name,isFolder,parent,++count);
        }else{
            return QString("(%1)").arg(QString::number(count));
        }
    }
}
