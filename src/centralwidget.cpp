#include "centralwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QSplitter>
#include <QScrollBar>

#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include "rendersettingtab.h"

//#include "dirselector.h"
//#include <QDebug>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    plateListTab = new PlateListTab;
    renderSettingTab = new RenderSettingTab;
    dirSettingTab = new DirSettingTab;

    tab = new QTabWidget;
//    tab->setDocumentMode(true);
//    tab->setStyleSheet("QTabWidget:tab-bar { left: 0em;} QTabBar:tab:selected{background-color:darkgray}");

     /*
     * 샷 리스트 뷰 화면
     */
    tab->addTab(plateListTab,"List");

    /*
     * 변환 포멧 설정 화면
     */
    tab->addTab(renderSettingTab,"setting");

    /*
     * 경로 설정 템플릿 화면
     */
    tab->addTab(dirSettingTab,"path");

    messageview = new QPlainTextEdit;
    messageview->setReadOnly(true);

    QVBoxLayout *viewlayout = new QVBoxLayout;
    viewlayout->setMargin(0);
    viewlayout->setContentsMargins(0,0,0,0);

    viewlayout->addWidget(tab);

    QWidget *topWidget = new QWidget;
    topWidget->setLayout(viewlayout);

    QSplitter *splitter = new QSplitter(Qt::Vertical);

    splitter->addWidget(topWidget);
    splitter->addWidget(messageview);

    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(splitter);

    setLayout(layout);

    connect(plateListTab,SIGNAL(searchingDir(QString)),this,SLOT(searchingDir(QString)));
    connect(plateListTab,SIGNAL(searchFinish(bool)),this,SLOT(searchFinish(bool)));
    connect(plateListTab,SIGNAL(findedSequence(QString)),this,SLOT(findedSequence(QString)));
}

void CentralWidget::searchingDir(QString dir)
{
    messageview->appendHtml("<font color=black>Searching........... "+dir+"</font>");
    QScrollBar *scrollbar = messageview->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void CentralWidget::searchFinish(bool finish)
{
    messageview->appendHtml("<font color=blue> Search Finish</font>");
    QScrollBar *scrollbar = messageview->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void CentralWidget::findedSequence(QString fileName)
{
    messageview->appendHtml("<font color=green> find sequence....." + fileName +"</font>");
    QScrollBar *scrollbar = messageview->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());

}

