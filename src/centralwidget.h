#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>
#include <QPushButton>
#include "platelisttab.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);


signals:

public slots:
    void printPath(QModelIndex index);

private:
    QTabWidget *tab;
    QTextBrowser *messageview;
//    QPushButton *upButton;
    QPushButton *downButton;
//    QFileSystemModel *fileModel;
//    QTreeView *dirView;

//    DirSelector *dirSelector;
//    PlateViewController *plateViewController;
    PlateListTab *plateListTab;



};

#endif // CENTRALWIDGET_H
