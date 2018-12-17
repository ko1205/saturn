#include "centralwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QSplitter>
//#include "dirselector.h"
//#include <QDebug>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    dirSelector = new DirSelector;
    plateViewController = new PlateViewController;

    QSplitter *mainSplitter = new QSplitter;

    mainSplitter->addWidget(dirSelector);
    mainSplitter->addWidget(plateViewController);

    mainSplitter->setStretchFactor(0,0);
    mainSplitter->setStretchFactor(1,1);

    /*
     * setCollapsible 합수는 Splitter 화면이 완전히 접혀 들어갈지
     * 여부를 판단 한다. (int index, bool collapse) index는 창순서, collapse는 true,false 값을 가진다.
     */
    mainSplitter->setCollapsible(0,false);
    mainSplitter->setCollapsible(1,false);

    tab = new QTabWidget;
//    tab->setDocumentMode(true);
//    tab->setStyleSheet("QTabWidget:tab-bar { left: 0em;} QTabBar:tab:selected{background-color:darkgray}");

     /*
     * 샷 리스트 뷰 화면
     */
    tab->addTab(mainSplitter,"List");

    /*
     * 변환 포멧 설정 화면
     */
    tab->addTab(new QWidget,"setting");

    /*
     * 경로 설정 템플릿 화면
     */
    tab->addTab(new QWidget,"path");

    messageview = new QTextBrowser;
//    messageview->setTextColor(QColor(Qt::black));
    messageview->setText("test");
    messageview->append("dsdlkjfslkf");


    QVBoxLayout *viewlayout = new QVBoxLayout;
    viewlayout->setMargin(0);
    viewlayout->setContentsMargins(0,0,0,0);

    viewlayout->addWidget(tab);

    QWidget *topWidget = new QWidget;
    topWidget->setLayout(viewlayout);

    QSplitter *splitter = new QSplitter(Qt::Vertical);

    splitter->addWidget(topWidget);
    splitter->addWidget(messageview);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(splitter);

    setLayout(layout);
//    connect(dirView,SIGNAL(clicked(QModelIndex)),this,SLOT(printPath(QModelIndex)));
}


void CentralWidget::printPath(QModelIndex index)
{
#ifdef QT_DEBUG
//    qDebug(fileModel->filePath(index).toLocal8Bit());
#endif
//    debugConsol(fileModel->filePath(index));
}
