#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <QDir>
#include <QString>


struct sequenceInfo
{
    QString filePath;
    QString sequenceName;
    int startFrame;
    int endFrame;
};

QList<sequenceInfo> searchSequence(const QString path);
QList<sequenceInfo> searchSequence(const QDir path);


#endif // COMMONFUNC_H
