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

}

void MainCentralWidget::searchSequence(const QString path)
{
    QDir rootPath = path;
    QStringList nameFilter = (QStringList() << "*.dpx" << "*.exr" << "*.jpg");
    QStringList imageFiles =  rootPath.entryList(nameFilter,QDir::Files|QDir::NoDotAndDotDot);
    QFileInfoList test2 =  rootPath.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);

    QRegExp regex("(\\S*[^0-9])?(\\d+)([\\S.]+[^.])$");
    QStringList out;

    while(imageFiles.count()!=0)
    {
        if(regex.indexIn(imageFiles.at(0)) != -1)
        {
            QString prefix = regex.cap(1);
            QString pedding = regex.cap(2);
            QString suffix = regex.cap(3);

            QString sequenceName = prefix + QString("%1") + suffix;

            int frameNum= pedding.toInt();
            out << sequenceName << QString::number(frameNum);

            int index;
            while((index = imageFiles.indexOf(sequenceName.arg(frameNum,pedding.count(),10,QLatin1Char('0')))) != -1)
            {
                sequenceName.arg(frameNum,pedding.count(),10,QLatin1Char('0'));
                imageFiles.removeAt(index);
                frameNum++;
            }
            out << QString::number(frameNum-1);

        }else{
             out << imageFiles.at(0);
            imageFiles.removeAt(0);
        }
    }
    qDebug() << out;
    return;
}

//void MainCentralWidget::test()
//{
//    QDir dir();
//    QStringList sequenceName;
//    QFileInfoList list = dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
//    while(list.count != 0)
//    {
//        QString fileName = list.at(0).fileName();
//        QRegExp regex("d+.a-z");
//        sequenceName.append(fileName);
//    }
//}
