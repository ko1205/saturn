#include "templateview.h"
#include <QMessageBox>
#include <QShortcut>
#include <QDebug>

TemplateView::TemplateView(QWidget *parent)
    :QTreeView(parent)
{
    fileCount = 0;
    templateModel = new QStandardItemModel;

    templateModel->setHorizontalHeaderLabels(QStringList()<<"Name" << "Type");

    createIcon();
    createRootFolder();

    setModel(templateModel);

    popupMenu = new QMenu(this);
    insertFolderAct = new QAction("Create Folder",this);
    newFile = new QAction("Create File",this);
    deleteAct = new QAction("Delete",this);
    deleteAllAct = new QAction("Delete All",this);

    popupMenu->addAction(insertFolderAct);
    popupMenu->addAction(newFile);
    popupMenu->addSeparator();
    popupMenu->addAction(deleteAct);
    popupMenu->addAction(deleteAllAct);

    /*
     * 현재 enter key로 edit 모드 진입시 old name이 저장 되지 않으므로
     * delegate 에서 재구현 할때 까지 DoubleClick 시에만 edit가 되도록 설정
     */
    setEditTriggers(QAbstractItemView::DoubleClicked);

    /*
     * deletekey 삭제 기능
     */
//    QShortcut *deleteKey = new QShortcut(QKeySequence(Qt::Key_Delete),this);
    QShortcut *deleteKey = new QShortcut(QKeySequence(Qt::Key_Backspace),this);

    connect(insertFolderAct,SIGNAL(triggered(bool)),this,SLOT(insertFolder()));
    connect(newFile,SIGNAL(triggered(bool)),this,SLOT(newFileSlot()));
    connect(deleteAct,SIGNAL(triggered(bool)),this,SLOT(deleteFolder()));
    connect(deleteAllAct,SIGNAL(triggered(bool)),this,SLOT(resetTemplate()));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(storOldName(QModelIndex)));
    connect(deleteKey,SIGNAL(activated()),this,SLOT(deleteFolder()));
    connect(templateModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(checkRename(QModelIndex)));
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(setinfo(QModelIndex)));
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
    rootItem->setData(0,Qt::UserRole);
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
    if(index.column() != 0)
    {
        index = templateModel->index(index.row(),0,index.parent());
    }
    /*
     * 선택된 Item이 폴더일 경우에만 children 생성
     * 폴더일떄 와 파일일때 함수구조가 같으므로 나중에 하나의 함수로 통합정리
     */
    if(index.data(Qt::UserRole).toInt())
    {
        index = index.parent();
    }
    QString folderName = "NewFolder%1";
//    folderName.arg("test Code");
    QString sub = autoRename(folderName,0,index);
    QStandardItem *newFolder = new QStandardItem(folderName.arg(sub));
    newFolder->setData(0,Qt::UserRole);
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
    pathPreviewIns->updatePrevew();
}

void TemplateView::newFileSlot()
{
    QModelIndex index = currentIndex();
    if(index.column() != 0)
    {
        index = templateModel->index(index.row(),0,index.parent());
    }
    if(index.data(Qt::UserRole).toInt())
    {
        index = index.parent();
    }
    QString fileName = "NewFile%1";
    QString sub = autoRename(fileName,1,index);
    QStandardItem *newFile = new QStandardItem(fileName.arg(sub));
    newFile->setData(1,Qt::UserRole);
    newFile->setData(5,Qt::UserRole+1);
    newFile->setData(1001,Qt::UserRole+2);
    newFile->setData(true,Qt::UserRole+3);
    newFile->setIcon(fileIcon);
    QStandardItem *type = new QStandardItem("file copy");
    type->setEditable(false);
    templateModel->itemFromIndex(index)->appendRow(QList<QStandardItem*>()<<newFile << type);
    fileCount++;
    rootItem->sortChildren(0);
    rootItem->sortChildren(1,Qt::DescendingOrder);
    expand(index);
    pathPreviewIns->updatePrevew();
}

void TemplateView::deleteFolder()
{
    QModelIndex index = currentIndex();
    if(index.column() != 0)
    {
        index = templateModel->index(index.row(),0,index.parent());
    }
    QStandardItem *item = templateModel->itemFromIndex(index);
    if(item != rootItem)
    {
        if(item->data(Qt::UserRole).toInt() != 0)
        {
            fileCount--;
        }else{
            fileCount -= countChildFile(item);
        }
        templateModel->removeRow(index.row(),item->parent()->index());
        qDebug()<<"delete Key!!!";
        pathPreviewIns->updatePrevew();
    }
}

void TemplateView::resetTemplate()
{
    int rowCount = rootItem->rowCount();
    rootItem->removeRows(0,rowCount);
    pathPreviewIns->updatePrevew();
    qDebug() << rowCount;

}

int TemplateView::countChildFile(QStandardItem *item)
{
    int childFileCount = 0;
    int row = item->rowCount();
    for(int i = 0; i < row ; i++)
    {
        QStandardItem *child = item->child(i);
        if(child->data(Qt::UserRole).toInt() != 0)
        {
            childFileCount++;
        }else{
            childFileCount += countChildFile(child);
        }
    }
    return childFileCount;
}

void TemplateView::setRootFolderName(QDir path)
{
    QString dirName = path.dirName();
    rootItem->setData(dirName,Qt::DisplayRole);
}

int TemplateView::checkSameName(QString name,int isFolder, const QModelIndex &parent)
{
    int count = 0;
    int rowCount = templateModel->rowCount(parent);
    for(int i=0;i<rowCount;i++)
    {
        QString rowName = parent.child(i,0).data().toString();
        int rowIsFolder = parent.child(i,0).data(Qt::UserRole).toInt();
       if(rowName.toUpper() == name.toUpper() && isFolder == rowIsFolder)
       {
           /*
            * 항상 자기 자신 한개가 존재 하므로 bool 형으로 처리가 되지 않아 count 로 2개 이상일때 를 체크
            */
           count++;
       }
    }
    return count;
}

QString TemplateView::autoRename(QString name, int isFolder, const QModelIndex &parent,int count)
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
    int isFolder = index.data(Qt::UserRole).toInt();
    QModelIndex parent = index.parent();
    QModelIndex typeIndex = templateModel->index(index.row(),1,parent);
    bool isSameName = false;
    QRegExp rx("[\\\\ \\/ \\: \? \" \\* \\< \\> \\|]");
    if(checkSameName(newName,isFolder,parent) == 2)
    {
        templateModel->setData(index,oldName,Qt::DisplayRole);
        QMessageBox::information(this,tr("Information"),tr("That Name Already Exists"),QMessageBox::Yes);
    }else if(newName.contains(rx) && index.column() == 0){
        templateModel->setData(index,oldName,Qt::DisplayRole);
        QMessageBox::information(this,"","Can not use \\ / : * ? \" < >",QMessageBox::Yes);
    }
    switch (isFolder) {
    case 1:
        templateModel->setData(typeIndex,"file copy",Qt::DisplayRole);
        break;
    case 2:
        templateModel->setData(typeIndex,"thumbnail",Qt::DisplayRole);
        break;
    case 3:
        templateModel->setData(typeIndex,"jpeg proxy",Qt::DisplayRole);
        break;
    case 4:
        templateModel->setData(typeIndex,"mov preview",Qt::DisplayRole);
    default:
        break;
    }
    pathPreviewIns->updatePrevew();

}

void TemplateView::setPathPreview(PathPreView *preview)
{
    pathPreviewIns = preview;
}

void TemplateView::setinfo(const QModelIndex &index)
{
    QModelIndex newIndex = index;
    QStandardItem *item;

    if(index.column() != 0)
    {
        newIndex = templateModel->index(index.row(),0,index.parent());
    }
    qDebug() << templateModel->data(newIndex,Qt::DisplayRole).toString();
    item = templateModel->itemFromIndex(newIndex);
    emit itemClickedView(item);
}

int TemplateView::getFileCount()
{
    return fileCount;
}

QStandardItem *TemplateView::root()
{
    return rootItem;
}
