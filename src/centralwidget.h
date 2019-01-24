#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include "platelisttab.h"
#include "rendersettingtab.h"
#include "dirsettingtab.h"
#include "renderthread.h"
#include <QProgressBar>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);


signals:

public slots:
    void searchingDir(QString dir);
    void searchFinish(bool finish);
    void findedSequence(QString fileName);
    void startRender();

private:
    QTabWidget *tab;
    QPlainTextEdit *messageview;
    QPushButton *downButton;

    PlateListTab *plateListTab;
    RenderSettingTab *renderSettingTab;
    DirSettingTab *dirSettingTab;
    RenderThread *renderThread;
};

#endif // CENTRALWIDGET_H
