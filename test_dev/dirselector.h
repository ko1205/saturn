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
    void setCurrnetPaht(QModelIndex);

private:
    QTreeView *dirTreeView;
    QFileSystemModel *fileSystemModel;
    QPushButton *selectorButton;
    QPushButton *cancelButton;
    QString currentPath;
};

#endif // DIRSELECTOR_H
