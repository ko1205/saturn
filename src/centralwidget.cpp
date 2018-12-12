#include "centralwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QSplitter>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    tab = new QTabWidget;
//    tab->setDocumentMode(true);
//    tab->setStyleSheet("QTabWidget:tab-bar { left: 0em;} QTabBar:tab:selected{background-color:darkgray}");

     /*
     * 샷 리스트 뷰 화면
     */
    tab->addTab(new QTableView,"List");

    /*
     * 변환 포멧 설정 화면
     */
    tab->addTab(new QWidget,"setting");

    /*
     * 경로 설정 템플릿 화면
     */
    tab->addTab(new QWidget,"path");

    messageview = new QTextBrowser;
    messageview->setTextColor(QColor(Qt::black));
    messageview->setText("test");
    messageview->append("dsdlkjfslkf");

    QVBoxLayout *layout = new QVBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Vertical);

    splitter->addWidget(tab);
    splitter->addWidget(messageview);

    layout->addWidget(splitter);
//    layout->addWidget(messageview);

    setLayout(layout);

}
