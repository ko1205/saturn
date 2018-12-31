#include "centralwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QSplitter>
#include <QScrollBar>

#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>

//#include "dirselector.h"
//#include <QDebug>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    plateListTab = new PlateListTab;
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
    QGroupBox *groupBox = new QGroupBox("Thumbnail Setting");
    groupBox->setCheckable(true);
    groupBox->setChecked(true);

    QLabel *width = new QLabel("Width Size : ");
    QLabel *height = new QLabel ("Height Size : ");

    QSpinBox *widthSpin = new QSpinBox;
    QSpinBox *heightSpin = new QSpinBox;

    QLabel *label = new QLabel("Jpge Quality");
    QSlider *slider = new QSlider(Qt::Horizontal);
    QSpinBox *spinBox = new QSpinBox();


    QGridLayout *inGroup = new QGridLayout;
    QSpacerItem *spacer = new QSpacerItem(0,0);

    inGroup->addWidget(width,0,0);
    inGroup->addWidget(height,1,0);
    inGroup->addWidget(widthSpin,0,1);
    inGroup->addWidget(heightSpin,1,1);

    inGroup->addWidget(label,2,0);
    inGroup->addWidget(slider,2,1,1,2);
    inGroup->addWidget(spinBox,2,3);

    inGroup->addItem(spacer,3,0);

    inGroup->setRowStretch(0,0);
    inGroup->setRowStretch(1,0);
    inGroup->setRowStretch(2,0);
    inGroup->setRowStretch(3,1);

    groupBox->setLayout(inGroup);

    QVBoxLayout *tabMain = new QVBoxLayout;
    tabMain->addWidget(groupBox);

    QWidget *settingTab = new QWidget;
    settingTab->setLayout(tabMain);

    tab->addTab(settingTab,"setting");

    /*
     * 경로 설정 템플릿 화면
     */
    tab->addTab(new QWidget,"path");

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

