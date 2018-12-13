#ifndef DIRSELECTOR_H
#define DIRSELECTOR_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>

class DirSelector : public QWidget
{
    Q_OBJECT
public:
    DirSelector(QWidget *parent = 0);

signals:

public slots:

private:
    QTreeView *dirTreeView;
    QFileSystemModel *fileSystmeModel;
};

#endif // DIRSELECTOR_H
