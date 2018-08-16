#ifndef MAINCENTRALWIDGET_H
#define MAINCENTRALWIDGET_H

#include <QWidget>

class QMdiArea;
class SubWindow;
class QMdiSubWindow;

class MainCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainCentralWidget(QWidget *parent = 0);
    SubWindow *creatSubWindow();

private:
    void createLayout();
    QMdiArea *m_mdiArea;
    SubWindow *currentSubwindow;

signals:
    void subWindowActivated(QMdiSubWindow*);

public slots:
    void newProject();
//    void subWindowChange();
};

#endif // CENTRALWIDGET_H
