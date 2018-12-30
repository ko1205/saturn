#include "searchthread.h"
#include "dpxreader.h"
#include "exrreader.h"
#include <QDebug>

SearchThread::SearchThread(PlateViewController *PlateController)
{
    controller = PlateController;
}

void SearchThread::run()
{

    status = true;
    searchPlateLoop(rootPath);
    emit searchFinish(true);
}

void SearchThread::setRootPath(QString path)
{
   rootPath = path;
}

void SearchThread::setStatus()
{
    status = false;
}

void SearchThread::searchPlateLoop(QDir path)
{
    if(status){
        QDir searchPath = path;
        emit searchingDir(path.absolutePath());
        searchSequence(path);
#ifdef QT_DEBUG
        qDebug() << "searching "+searchPath.absolutePath();
#endif
        QStringList dirList = searchPath.entryList(QDir::AllDirs|QDir::NoDotAndDotDot);
        foreach (QString dir, dirList) {
            searchPath.cd(dir);
            searchPlateLoop(searchPath);
            searchPath.cd("..");
        }
    }else{
        return;
    }
}

void SearchThread::searchSequence(const QDir path)
{
    PlateItem item;
    QString sequence;
    QStringList nameFilter = (QStringList() << "*.dpx" << "*.exr" << "*.jpg" << "*.jpeg");
    QStringList imageFiles =  path.entryList(nameFilter,QDir::Files|QDir::NoDotAndDotDot);

    QRegExp regex("(\\S*[^0-9])?(\\d+)([\\S.]+[^.])$");
    while(imageFiles.count()!=0)
    {
        if(regex.indexIn(imageFiles.first()) != -1)
        {
            QString prefix = regex.cap(1);
            QString padding = regex.cap(2);
            QString suffix = regex.cap(3);

            QString sequenceName = prefix + QString("%1") + suffix;

            long long frameNum= padding.toLongLong();
            sequence = sequenceName.arg("#",padding.count(),QLatin1Char('#'));
            item.fileName = sequence;
            item.frame.first = frameNum;
            item.firstFileName = imageFiles.first();

//            item.sequenceName = sequenceName;
//            item.startFrame = frameNum;

            int index;
            while((index = imageFiles.indexOf(sequenceName.arg(frameNum,padding.count(),10,QLatin1Char('0')))) != -1)
            {
                imageFiles.removeAt(index);
                frameNum++;
            }
            item.frame.second = frameNum-1;
//            item.endFrame = frameNum-1;

        }else{
//             item.sequenceName = imageFiles.first();
//             item.startFrame = -1;
//             item.endFrame = -1;
            sequence = imageFiles.first();
//            imageFiles.removeFirst();

            item.fileName = sequence;
            item.firstFileName = imageFiles.first();
            item.frame.first = -1;
            item.frame.second = -1;

            imageFiles.removeFirst();
        }
//        sequenceItems.append(item);
        emit findedSequence(sequence);
        item.path = path;

        finalizeItem(item);
        controller->findedSequence(item);
    }
//    return sequenceItems;

}

void SearchThread::finalizeItem(PlateItem &item)
{
#include <QFileInfo>
    QFileInfo fileName(item.path,item.firstFileName);
    QString ext = fileName.suffix();
    QStringList extType = {"jpg","jpeg","dpx","exr"};
    QImage image;
    if(item.frame.first == item.frame.second)
    {
        item.singleFrame = true;
        item.fileName = item.firstFileName;
    }else{
        item.singleFrame = false;
    }

    switch (extType.indexOf(ext.toLower())) {
    case 0:
        if(image.load(fileName.absoluteFilePath())){
            item.thumbnail = image;
        }else{
            /*
             * 이미지 로딩 실패시 표시할 이미지 로딩
             */
        }
        break;
    case 1:
         if(image.load(fileName.absoluteFilePath())){
            item.thumbnail = image;
        }else{
             /*
              * 이미지 로딩 실패시 표시할 이미지 로딩
              */
        }
        break;
    case 2:
        DpxReader dpxReader(fileName.absoluteFilePath());
        if(dpxReader.isValid)
        {
            item.thumbnail = dpxReader.getQImage();
        }else{
            /*
             * 이미지 로딩 실패시 표시할 이미지 로딩
             */
        }
        break;
    case 3:
        int aa;
//        ExrReader exrReader(fileName.absoluteFilePath());
//        if(exrReader.isValid)
//        {
//            item.thumbnail = exrReader.getQImage();
//        }else{
//            /*
//             * 이미지 로딩 실패시 표시할 이미지 로딩
//             */

//        }
        break;
    }

}
