#include "renderthread.h"
#include <QDebug>
#include <Python.h>

RenderThread::RenderThread(QObject *parent)
    :QThread(parent)
{
//    Py_Initialize();

}

void RenderThread::run()
{
    status = true;
    int plateListCount = plateListModel->rowCount();
    int templateFileCount = templateView->getFileCount();
    int processCount = plateListCount*templateFileCount;
    emit renderStart(processCount);
    targetPath = "/Users/ghchoi/Desktop/test";
    for(int i = 0; i < plateListCount;i++)
    {
        currentItem = plateListModel->getItem(i);
        QModelIndex templateRoot = templateModel->index(0,0);
        readTemplateLoop(templateRoot,targetPath);
    }

    qDebug() << "render Thread run";
//    qDebug() << plateListCount;
//    qDebug() << templateFileCount;
//    qDebug() << processCount;
}

void RenderThread::setPlateListModel(QAbstractItemModel *model)
{
    plateListModel = qobject_cast<PlateItemModel*>(model);
}

void RenderThread::setTemplateModel(QStandardItemModel *model)
{
    templateModel = model;
}

void RenderThread::setTemplateView(TemplateView *view)
{
    templateView = view;

}

void RenderThread::setRenderSetting(RenderSettingTab *settingTab)
{
    renderSetting = settingTab;
}

void RenderThread::readTemplateLoop(QModelIndex index,QDir path)
{
    QStandardItem *item = templateModel->itemFromIndex(index);
    int type = item->data(Qt::UserRole).toInt();
    if(index.parent() == QModelIndex())
    {
        int count = item->rowCount();
        for(int i = 0 ; i < count; i++)
        {
            QModelIndex childIndex = templateModel->index(i,0,index);
            readTemplateLoop(childIndex,path);
        }
    }else{
        QString templateName = item->data(Qt::DisplayRole).toString();
        QString targetName = replaceName(templateName);
        int count =item->rowCount();
        switch (type) {
        case 0:
            path.mkdir(targetName);
            path.cd(targetName);
            for(int i = 0 ; i < count; i++)
            {
                QModelIndex childIndex = templateModel->index(i,0,index);
                readTemplateLoop(childIndex,path);
            }
            break;
        case 1:
        {
            QDir orgPath = currentItem->path;
            if(!currentItem->singleFrame)
            {
                sequenceFileCopy(item,path,targetName);

            }else{
                QFileInfo orgFile(orgPath.absoluteFilePath(currentItem->firstFileName));
                QString ext = orgFile.suffix();
                QFile::copy(orgFile.absoluteFilePath(),path.absoluteFilePath(targetName+"."+ext));
            }
        }
            emit processDone();
            break;
        default:
            break;
        }
    }
}

QString RenderThread::replaceName(QString name)
{
    QString sceneData = currentItem->secne;
    name.replace("[scene]",sceneData);

    QString shotData = currentItem->shot;
    name.replace("[shot]",shotData);

    QString subnameData = currentItem->subName;
    name.replace("[subname]",subnameData);

    QString orgName = currentItem->fileName;
    QFileInfo orgFileInfo(orgName);
    name.replace("[filename]",orgFileInfo.baseName().replace("#",""));

    return name;
}

void RenderThread::sequenceFileCopy(QStandardItem *item,QDir path, QString targetName)
{
    bool isRenumbering = item->data(Qt::UserRole+3).toBool();
    int pending = item->data(Qt::UserRole+1).toInt();
    int start = item->data(Qt::UserRole+2).toInt();
    QDir orgPath = currentItem->path;
    QString orgFIlename = currentItem->fileName;
    int orgStartNum = currentItem->frame.first;
    int orgEndNum = currentItem->frame.second;
    int druration = orgEndNum - orgStartNum + 1;
    int targetStartNum;
    int orgPendingCount = currentItem->pendingCount;

    if(isRenumbering)
    {
        targetStartNum = start;
    }else{
        targetStartNum = orgStartNum;
        pending = orgPendingCount;
    }

    for(int i = 0; i < druration; i++)
    {
        QString realFIleName = replaceOrgName(orgFIlename,orgStartNum,orgPendingCount);
        QFileInfo orgFileInfo(currentItem->path,realFIleName);

        qDebug() << orgFileInfo.absoluteFilePath();
        QString realTargetName = (targetName+".%1."+orgFileInfo.suffix()).arg(targetStartNum,pending,10,QLatin1Char('0'));
        QFileInfo targetFileInfo(path,realTargetName);
        orgStartNum++;
        targetStartNum++;

        QFile::copy(orgFileInfo.absoluteFilePath(),targetFileInfo.absoluteFilePath());



//            QDir orgPath = currentItem->path;
//            if(!currentItem->singleFrame)
//            {
//                sequenceFileCopy(item,path,targetName);

//            }else{
//                QFileInfo orgFile(orgPath.absoluteFilePath(currentItem->firstFileName));
//                QString ext = orgFile.suffix();
//                QFile::copy(orgFile.absoluteFilePath(),path.absoluteFilePath(targetName+"."+ext));
    }


}

QString RenderThread::replaceOrgName(QString filename,int num, int pendingCount)
{
    QRegExp regex("[#]+");
    return filename.replace(regex,"%1").arg(num,pendingCount,10,QLatin1Char('0'));
}
