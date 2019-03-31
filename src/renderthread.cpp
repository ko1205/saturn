#include "renderthread.h"
#include <QDebug>
#include "dpxreader.h"
#include "exrreader.h"
#include <Python.h>
#include "createmov.h"

RenderThread::RenderThread(QObject *parent)
    :QThread(parent)
{
    Py_Initialize();

}

void RenderThread::run()
{
////////////////////temp code //////////////////////
    QString fileListString = targetPath.absolutePath() + "/tempList.txt";
    fileList = new QFile(fileListString);
    fileList->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(fileList);
////////////////////////////////////////////////////
    status = true;
    int plateListCount = plateListModel->rowCount();
    int templateFileCount = templateView->getFileCount();
    int processCount = plateListCount*templateFileCount;
    emit renderStart(processCount);
//    targetPath = "/Users/ghchoi/Desktop/test";
    for(int i = 0; i < plateListCount;i++)
    {
        currentItem = plateListModel->getItem(i);
        *out << currentItem->secne << "|" + currentItem->shot << "|" + currentItem->subName;
        QModelIndex templateRoot = templateModel->index(0,0);
        readTemplateLoop(templateRoot,targetPath);
        *out << endl;
    }

    qDebug() << "render Thread run";
//    qDebug() << plateListCount;
//    qDebug() << templateFileCount;
//    qDebug() << processCount;
    fileList->close();
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
                *out << "|" + path.absolutePath() << "|" + QString::number(0) << "|" + QString::number(0);
                QFileInfo orgFile(orgPath.absoluteFilePath(currentItem->firstFileName));
                QString ext = orgFile.suffix();
                QFile::copy(orgFile.absoluteFilePath(),path.absoluteFilePath(targetName+"."+ext));
            }
        }
            emit processDone();
            break;
        case 2:
            makeThumbnail(path,targetName);
            emit processDone();
            break;
        case 3:
            makeJpegProxy(item,path,targetName);
            emit processDone();
            break;
        case 4:
            makePreviewMov(path,targetName);
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

    *out << "|" + path.absolutePath() << "|" + QString::number(targetStartNum) << "|" + QString::number(targetStartNum + druration-1);

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

void RenderThread::makeThumbnail(QDir path, QString targetName)
{
    QString fileName = currentItem->firstFileName;
    QDir orgPath = currentItem->path;
    QFileInfo firstFileInfo(orgPath,fileName);
    QStringList extType = {"jpg","jpeg","dpx","exr"};
    QString ext = firstFileInfo.suffix();
    QImage image;
    QFileInfo targetFileInfo(path,targetName+".jpg");
    switch (extType.indexOf(ext.toLower())) {
    case 0:
        image.load(firstFileInfo.absoluteFilePath());
        break;
    case 1:
        image.load(firstFileInfo.absoluteFilePath());
        break;
    case 2:
    {
        DpxReader dpxReader(firstFileInfo.absoluteFilePath());
        if(dpxReader.isValid)
        {
            image = dpxReader.getQImage();
        }
    }
        break;
    case 3:
    {
        ExrReader exrReader(firstFileInfo.absoluteFilePath());
        if(exrReader.isValid)
        {
            image = exrReader.getQImage();
        }
    }
        break;
    default:
        break;
    }
    int width = renderSetting->getThumbnailWidth();
    int height = renderSetting->getThumbnailHeight();
    int quality = renderSetting->getThumbnailQuality();
    image = image.scaled(width,height,Qt::KeepAspectRatio);
    image.save(targetFileInfo.absoluteFilePath(),"jpg",quality);
    *out << "|" + targetFileInfo.absoluteFilePath();

}

void RenderThread::makeJpegProxy(QStandardItem *item, QDir path, QString targetName)
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
    QFileInfo orgFileInfo;
    QFileInfo targetFileInfo;
    QImage image;

    if(!currentItem->singleFrame)
    {

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
            orgFileInfo = QFileInfo(currentItem->path,realFIleName);

            //        qDebug() << orgFileInfo.absoluteFilePath();
            QString realTargetName = (targetName+".%1.jpg").arg(targetStartNum,pending,10,QLatin1Char('0'));
            targetFileInfo = QFileInfo(path,realTargetName);
            orgStartNum++;
            targetStartNum++;
            image = loadImage(orgFileInfo);
            if(renderSetting->isProxyReScale())
            {
                int width = renderSetting->getProxyWidth();
                int height = renderSetting->getProxyHeight();
                image = image.scaled(width,height,Qt::KeepAspectRatio);

                qDebug() << orgFileInfo.absoluteFilePath() << targetFileInfo.absoluteFilePath() << width << height;
            }
            int quality = renderSetting->getProxyQuality();
            image.save(targetFileInfo.absoluteFilePath(),"jpg",quality);
        }
    }else{
        orgFileInfo = QFileInfo(currentItem->path,currentItem->firstFileName);
        targetFileInfo = QFileInfo(path,targetName + ".jpg");
        image = loadImage(orgFileInfo);
        if(renderSetting->isProxyReScale())
        {
            int width = renderSetting->getProxyWidth();
            int height = renderSetting->getProxyHeight();
            image = image.scaled(width,height,Qt::KeepAspectRatio);
        }
        int quality = renderSetting->getProxyQuality();
        image.save(targetFileInfo.absoluteFilePath(),"jpg",quality);
    }
}

QImage RenderThread::loadImage(QFileInfo file)
{
    QString ext = file.suffix();
    QStringList extType = {"jpg","jpeg","dpx","exr"};
    QImage image;
    switch (extType.indexOf(ext.toLower())) {
    case 0:
        image.load(file.absoluteFilePath());
        break;
    case 1:
        image.load(file.absoluteFilePath());
        break;
    case 2:
    {
        DpxReader dpxReader(file.absoluteFilePath());
        if(dpxReader.isValid)
        {
            image = dpxReader.getQImage();
        }
    }
        break;
    case 3:
    {
        ExrReader exrReader(file.absoluteFilePath());
        if(exrReader.isValid)
        {
            image = exrReader.getQImage();
        }
    }
        break;
    default:
        break;
    }
    return image;
}

void RenderThread::makePreviewMov(QDir path, QString targetName)
{
    QFileInfo targetFileInfo(path,targetName+".mov");
    CreateMov movMaker;
    movMaker.setOutFile(targetFileInfo);

    QDir orgPath = currentItem->path;
    QString orgFIlename = currentItem->fileName;
    int orgStartNum = currentItem->frame.first;
    int orgEndNum = currentItem->frame.second;
    int druration = orgEndNum - orgStartNum + 1;
    int orgPendingCount = currentItem->pendingCount;
    QFileInfo orgFileInfo;
    QImage image;
    orgFileInfo = QFileInfo(currentItem->path,currentItem->firstFileName);
    image = loadImage(orgFileInfo);
    image = image.scaled(1920,1080,Qt::KeepAspectRatio);

    movMaker.setSize(image.width(),image.height());
    movMaker.setFrameRate(24);
    movMaker.avinit();
    movMaker.avFrameSetting();

    if(!currentItem->singleFrame)
    {
        for(int i = 0; i < druration; i++)
        {
            QString realFIleName = replaceOrgName(orgFIlename,orgStartNum,orgPendingCount);
            orgFileInfo = QFileInfo(currentItem->path,realFIleName);

            orgStartNum++;
            image = loadImage(orgFileInfo);
            image = image.scaled(1920,1080,Qt::KeepAspectRatio);
            if(i == (druration -1)){
                movMaker.getVideoFrame(image,i,true);
            }else{
                movMaker.getVideoFrame(image,i,false);
            }
        }
        movMaker.releaseMov();
    }

}

void RenderThread::setTargetPath(QDir path)
{
    targetPath = path;
}
