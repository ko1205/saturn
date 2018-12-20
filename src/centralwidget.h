#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTabWidget>
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
    void searchingDir(QString dir);
    void searchFinish(bool finish);

private:
    QTabWidget *tab;
    QPlainTextEdit *messageview;
    QPushButton *downButton;

    PlateListTab *plateListTab;



};

#endif // CENTRALWIDGET_H
