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
