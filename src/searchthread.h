#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QDir>
#include "plateviewcontroller.h"

class SearchThread : public QThread
{
    Q_OBJECT

public:
    SearchThread(PlateViewController *plateController);
    void setRootPath(QString path);
    void setStatus();

signals:
    void searchFinish(bool finish);
    void searchingDir(QString dir);
    void findedSequence(QString fileName);

protected:
    void run();

private:
    QString rootPath;
    PlateViewController *controller;
    bool status;
    void searchPlateLoop(QDir path);
    void searchSequence(const QDir path);

};

#endif // SEARCHTHREAD_H
