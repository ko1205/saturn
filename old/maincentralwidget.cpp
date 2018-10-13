#include "maincentralwidget.h"
#include <QMdiArea>
#include <QHBoxLayout>
#include <QMessageBox>
#include "subwindow.h"

#include <QDir>
#include <QDebug>

MainCentralWidget::MainCentralWidget(QWidget *parent) : QWidget(parent)
{
    createLayout();
}

void MainCentralWidget::createLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();
    m_mdiArea = new QMdiArea();
    QWidget *temp = new QWidget;   //뭘 만들어 넣을지 고민중
    temp->setBaseSize(300,500);
    layout->addWidget(m_mdiArea);
    layout->addWidget(temp);
    layout->setMargin(0);
    setLayout(layout);

//    connect(m_mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT());  // test code
}

SubWindow *MainCentralWidget::creatSubWindow()
{
    SubWindow *subwindow = new SubWindow;
    m_mdiArea->addSubWindow(subwindow);
    return subwindow;
}

bool MainCentralWidget::newProject(const QString path)
{
    static int num;

//    QMessageBox::information(this,"test",path,QMessageBox::Yes); //test code
//    searchSequence(path);   //test code 이 함수는 테스트후 다른 쓰레드로 이동
    QList<sequenceInfo> sequenceItems;
    sequenceItems.append(scanFolderLoop(path));
    currentSubwindow = creatSubWindow();
    currentSubwindow->setWindowTitle(tr("test[*]"));

    for(int i=0;sequenceItems.count()>i;i++)
    {
        qDebug() << sequenceItems[i].sequenceName << QString::number(sequenceItems[i].startFrame) << QString::number(sequenceItems[i].endFrame);
        currentSubwindow->appendItem(sequenceItems[i]);
    }
    currentSubwindow->showMaximized();
    currentSubwindow->setWindowModified(true);

    return true;

}


QList<sequenceInfo> MainCentralWidget::scanFolderLoop(const QString path)
{
    QList<sequenceInfo> list;
    list << searchSequence(path);
    QDir rootDir = path;
    QStringList dirList =  rootDir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot);
    foreach (QString dir, dirList) {
        QString subDir = path+"/"+dir;
        list << scanFolderLoop(subDir);
    }
    return list;
}
