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

    QMessageBox::information(this,"test",path,QMessageBox::Yes); //test code
    searchSequence(path);   //test code 이 함수는 테스트후 다른 쓰레드로 이동
    currentSubwindow = creatSubWindow();
    currentSubwindow->setWindowTitle(tr("test[*]"));
    currentSubwindow->showMaximized();
    currentSubwindow->setWindowModified(true);

    return true;

}

void MainCentralWidget::searchSequence(const QString path)
{
    QDir rootPath = path;
    QStringList nameFilter = (QStringList() << "*.dpx" << "*.exr" << "*.jpg" << "*.jpeg");
    QStringList imageFiles =  rootPath.entryList(nameFilter,QDir::Files|QDir::NoDotAndDotDot);
    QFileInfoList test2 =  rootPath.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);

    QRegExp regex("(\\S*[^0-9])?(\\d+)([\\S.]+[^.])$");
    QStringList out;
    QList<sequenceInfo> sequenceItems;

    while(imageFiles.count()!=0)
    {
         sequenceInfo item;
        if(regex.indexIn(imageFiles.at(0)) != -1)
        {
            QString prefix = regex.cap(1);
            QString padding = regex.cap(2);
            QString suffix = regex.cap(3);

            QString sequenceName = prefix + QString("%1") + suffix;

            int frameNum= padding.toInt();
            out << sequenceName << QString::number(frameNum);

            item.sequenceName=sequenceName;
            item.start = frameNum;

            int index;
            while((index = imageFiles.indexOf(sequenceName.arg(frameNum,padding.count(),10,QLatin1Char('0')))) != -1)
            {
                imageFiles.removeAt(index);
                frameNum++;
            }
            out << QString::number(frameNum-1);
            item.end = frameNum-1;

        }else{
             out << imageFiles.at(0);
             item.sequenceName = imageFiles.at(0);
             item.start = -1;
             item.end = -1;
            imageFiles.removeAt(0);
        }
        sequenceItems.append(item);
    }
    qDebug() << sequenceItems.count();
    for(int i=0;sequenceItems.count()>i;i++)
    {
        qDebug() << sequenceItems[i].sequenceName << QString::number(sequenceItems[i].start) << QString::number(sequenceItems[i].end);
    }
    return;
}
