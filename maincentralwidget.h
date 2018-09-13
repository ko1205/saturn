#ifndef MAINCENTRALWIDGET_H
#define MAINCENTRALWIDGET_H

#include <QWidget>

class QMdiArea;
class SubWindow;
class QMdiSubWindow;

struct sequenceInfo
{
    QString sequenceName;
    int start;
    int end;

};

class MainCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainCentralWidget(QWidget *parent = 0);
    SubWindow *creatSubWindow();

private:
    void createLayout();
    QList<sequenceInfo> searchSequence(const QString path);
    QList<sequenceInfo> scanFolderLoop(const QString path);

    QMdiArea *m_mdiArea;
    SubWindow *currentSubwindow;

signals:
    void subWindowActivated(QMdiSubWindow*);

public slots:
    bool newProject(const QString path);
//    void subWindowChange();
};

#endif // CENTRALWIDGET_H
