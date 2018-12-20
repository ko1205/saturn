#include "platelisttab.h"
#include <QSplitter>
#include <QGridLayout>
#include <QtDebug>

PlateListTab::PlateListTab(QWidget *parent) : QWidget(parent)
{
    dirSelector = new DirSelector;
    plateViewController = new PlateViewController;

    QSplitter *splitter = new QSplitter;

    splitter->addWidget(dirSelector);
    splitter->addWidget(plateViewController);

    /*
     * setStretchFactor(int index,int stretch) 함수는 Splitter창이 늘어날때 같이 늘어날지 여부를 결정
     */
    splitter->setStretchFactor(0,0);
    splitter->setStretchFactor(1,1);

     /*
     * setCollapsible 합수는 Splitter 화면이 완전히 접혀 들어갈지
     * 여부를 판단 한다. (int index, bool collapse) index는 창순서, collapse는 true,false 값을 가진다.
     */
    splitter->setCollapsible(0,false);
    splitter->setCollapsible(1,false);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(splitter);
    layout->setMargin(0);

    setLayout(layout);

    searchThread = new SearchThread;

    connect(dirSelector,SIGNAL(clickedSearchButton(QString)),this,SLOT(searchPlate(QString)));
    connect(dirSelector,SIGNAL(clickedCancelButton(bool)),this,SLOT(searchCancel()));
    connect(searchThread,SIGNAL(searchFinish(bool)),dirSelector,SLOT(setEnableCancelButton(bool)));
    connect(searchThread,SIGNAL(searchingDir(QString)),this,SIGNAL(searchingDir(QString)));
    connect(searchThread,SIGNAL(searchFinish(bool)),this,SIGNAL(searchFinish(bool)));
    connect(searchThread,SIGNAL(findedSequence(QString)),this,SIGNAL(findedSequence(QString)));
}

void PlateListTab::searchPlate(QString path)
{
    searchThread->setRootPath(path);
    searchThread->start();
}

void PlateListTab::searchCancel()
{
    searchThread->setStatus();
}
