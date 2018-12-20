#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>
#include <QPlainTextEdit>
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
    void searchingDir(QString dir);
    void searchFinish(bool finish);

private:
    QTabWidget *tab;
//    QTextBrowser *messageview;
    QPlainTextEdit *messageview;
//    QPushButton *upButton;
    QPushButton *downButton;
//    QFileSystemModel *fileModel;
//    QTreeView *dirView;

//    DirSelector *dirSelector;
//    PlateViewController *plateViewController;
    PlateListTab *plateListTab;



};

#endif // CENTRALWIDGET_H
