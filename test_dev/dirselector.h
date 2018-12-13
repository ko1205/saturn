#ifndef DIRSELECTOR_H
#define DIRSELECTOR_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>

class DirSelector : public QWidget
{
    Q_OBJECT
public:
    DirSelector(QWidget *parent = 0);

signals:

public slots:

private:
    QTreeView *dirTreeView;
    QFileSystemModel *fileSystemModel;
    QPushButton *selectorButton;
};

#endif // DIRSELECTOR_H
