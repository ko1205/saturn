#include "centralwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QSplitter>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    fileModel = new QFileSystemModel;
    fileModel->setRootPath("");
    dirView = new QTreeView;


    dirView->setModel(fileModel);
//    dirView->setStyleSheet("background-color:darkgray");

    QSplitter *mainSplitter = new QSplitter;

    mainSplitter->addWidget(dirView);
    mainSplitter->addWidget(new QTableView);
    tab = new QTabWidget;
//    tab->setContentsMargins(0,0,0,0);
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

//   	fileModel = new QFileSystemModel;
//    fileModel->setRootPath("/");
//    dirView = new QTreeView;

//    dirView->setModel(fileModel);

//    QSplitter *mainSplitter = new QSplitter;

//    mainSplitter->addWidget(dirView);
//    mainSplitter->addWidget(new QTableView);


    QVBoxLayout *layout = new QVBoxLayout;
    QVBoxLayout *viewlayout = new QVBoxLayout;

    viewlayout->setMargin(0);
    viewlayout->setContentsMargins(0,0,0,0);

    QWidget *topWidget = new QWidget;

    topWidget->setLayout(viewlayout);


    upButton = new QPushButton("UP");
    viewlayout->addWidget(tab);
    viewlayout->addWidget(upButton);

    QSplitter *splitter = new QSplitter(Qt::Vertical);

    splitter->addWidget(topWidget);
    splitter->addWidget(messageview);

    layout->addWidget(splitter);
//    layout->addWidget(messageview);

    setLayout(layout);

}
