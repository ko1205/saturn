#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);


signals:

public slots:

private:
    QTabWidget *tab;
    QTextBrowser *messageview;

};

#endif // CENTRALWIDGET_H
