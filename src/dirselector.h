#ifndef DIRSELECTOR_H
#define DIRSELECTOR_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>
#include <QDialog>

//class test : public QDialog
//{
//    Q_OBJECT
//public:
//    test();
//};

class DirSelector : public QWidget
{
    Q_OBJECT
public:
    DirSelector(QWidget *parent = 0);

signals:
    void clickedSearchButton(QString path);
    void clickedCancelButton(bool);

public slots:
    void setCurrnetPaht(QModelIndex);
    void setEnableCancelButton(bool isClicked);

private:
    QTreeView *dirTreeView;
    QFileSystemModel *fileSystemModel;
    QPushButton *searchButton;
    QPushButton *cancelButton;
    QString currentPath;
};

#endif // DIRSELECTOR_H
