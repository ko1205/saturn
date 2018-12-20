#include "searchthread.h"
#include <QDebug>

SearchThread::SearchThread()
{

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

//            item.sequenceName = sequenceName;
//            item.startFrame = frameNum;

            int index;
            while((index = imageFiles.indexOf(sequenceName.arg(frameNum,padding.count(),10,QLatin1Char('0')))) != -1)
            {
                imageFiles.removeAt(index);
                frameNum++;
            }
//            item.endFrame = frameNum-1;

        }else{
//             item.sequenceName = imageFiles.first();
//             item.startFrame = -1;
//             item.endFrame = -1;
            sequence = imageFiles.first();
            imageFiles.removeFirst();
        }
//        sequenceItems.append(item);
        emit findedSequence(sequence);
    }
//    return sequenceItems;

}
