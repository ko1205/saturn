#include "templateview.h"
#include <QMessageBox>

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

    /*
     * 현재 enter key로 edit 모드 진입시 old name이 저장 되지 않으므로
     * delegate 에서 재구현 할때 까지 DoubleClick 시에만 edit가 되도록 설정
     */
    setEditTriggers(QAbstractItemView::DoubleClicked);

    connect(insertFolderAct,SIGNAL(triggered(bool)),this,SLOT(insertFolder()));
    connect(newFile,SIGNAL(triggered(bool)),this,SLOT(newFileSlot()));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(storOldName(QModelIndex)));
    connect(templateModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(checkRename(QModelIndex)));
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
    QStandardItem *type = new QStandardItem("folder");
    type->setEditable(false);
    templateModel->appendRow(QList<QStandardItem*>()<<rootItem << type);
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
    QStandardItem *type = new QStandardItem("folder");
    type->setEditable(false);
    templateModel->itemFromIndex(index)->appendRow(QList<QStandardItem*>()<< newFolder << type);

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
    QString fileName = "NewFile%1";
    QString sub = autoRename(fileName,false,index);
    QStandardItem *newFile = new QStandardItem(fileName.arg(sub));
    newFile->setData(false,Qt::UserRole);
    newFile->setIcon(fileIcon);
    QStandardItem *type = new QStandardItem("file");
    type->setEditable(false);
    templateModel->itemFromIndex(index)->appendRow(QList<QStandardItem*>()<<newFile << type);
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

int TemplateView::checkSameName(QString name,bool isFolder, const QModelIndex &parent)
{
    int count = 0;
    int rowCount = templateModel->rowCount(parent);
    for(int i=0;i<rowCount;i++)
    {
        QString rowName = parent.child(i,0).data().toString();
        bool rowIsFolder = parent.child(i,0).data(Qt::UserRole).toBool();
       if(rowName.toUpper() == name.toUpper() && isFolder == rowIsFolder)
       {
           count++;
       }
    }
    return count;
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

void TemplateView::storOldName(const QModelIndex &index)
{
    oldName = index.data().toString();
}

void TemplateView::checkRename(const QModelIndex &index)
{
    /*
     * 이름 체크 부분에서 enter key 로 수정 모드 진입시 old name 저장이 되지 않는다.
     * 나중에 delegate에서 edit 모드 진입시에 체크 하게 변경할 필요 있음
     */
    QString newName = index.data().toString();
    bool isFolder = index.data(Qt::UserRole).toBool();
    QModelIndex parent = index.parent();
    bool isSameName = false;
    QRegExp rx("[\\\\ \\/ \\: \? \" \\* \\< \\> \\|]");
    if(checkSameName(newName,isFolder,parent) == 2)
    {
        templateModel->setData(index,oldName,Qt::DisplayRole);
        QMessageBox::information(this,tr("Information"),tr("That Name Already Exists"),QMessageBox::Yes);
    }else if(newName.contains(rx)){
        templateModel->setData(index,oldName,Qt::DisplayRole);
        QMessageBox::information(this,"","Can not use \\ / : * ? \" < >",QMessageBox::Yes);
    }

}
