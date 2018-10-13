#include <QRegExp>
#include "commonfunc.h"

QList<sequenceInfo> searchSequence(const QDir path)
{
    QStringList nameFilter = (QStringList() << "*.dpx" << "*.exr" << "*.jpg" << "*.jpeg");
    QStringList imageFiles =  path.entryList(nameFilter,QDir::Files|QDir::NoDotAndDotDot);

    QRegExp regex("(\\S*[^0-9])?(\\d+)([\\S.]+[^.])$");
    QList<sequenceInfo> sequenceItems;

    while(imageFiles.count()!=0)
    {
        sequenceInfo item;
        item.filePath = path.absolutePath();
        if(regex.indexIn(imageFiles.first()) != -1)
        {
            QString prefix = regex.cap(1);
            QString padding = regex.cap(2);
            QString suffix = regex.cap(3);

            QString sequenceName = prefix + QString("%1") + suffix;

            int frameNum= padding.toInt();

            item.sequenceName = sequenceName;
            item.startFrame = frameNum;

            int index;
            while((index = imageFiles.indexOf(sequenceName.arg(frameNum,padding.count(),10,QLatin1Char('0')))) != -1)
            {
                imageFiles.removeAt(index);
                frameNum++;
            }
            item.endFrame = frameNum-1;

        }else{
             item.sequenceName = imageFiles.first();
             item.startFrame = -1;
             item.endFrame = -1;
             imageFiles.removeFirst();
        }
        sequenceItems.append(item);
    }
    return sequenceItems;

}

QList<sequenceInfo> searchSequence(const QString path)
{
    QDir dir(path);
    return searchSequence(dir);
}
