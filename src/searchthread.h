#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include <QDir>

class SearchThread : public QThread
{
    Q_OBJECT

public:
    SearchThread();
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
    bool status;
    void searchPlateLoop(QDir path);
    void searchSequence(const QDir path);

};

#endif // SEARCHTHREAD_H
