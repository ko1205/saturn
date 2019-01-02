#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>
#include "rendersettingtab.h"

RenderSettingTab::RenderSettingTab(QWidget *parent) : QWidget(parent)
{

    mainLayout = new QGridLayout;

    mainLayout->addWidget(createThumbnailSetting(),0,0);
    mainLayout->addWidget(createJpegProxySetting(),0,1);
    mainLayout->addWidget(createTacticdbSetting(),1,0);
    mainLayout->addWidget(createQuickMovSetting(),1,1);

    setLayout(mainLayout);

}

QGroupBox *RenderSettingTab::createThumbnailSetting()
{
    QGroupBox *thumbnailSettingGrp = new QGroupBox("Thumbnail Setting");
    thumbnailSettingGrp->setCheckable(true);
    thumbnailSettingGrp->setChecked(true);

    QLabel *thumbnailWidthLabel = new QLabel("Width Size : ");
    QLabel *thumbnailHeightLabel = new QLabel("Height Size : ");

    QSpinBox *thumbnailWidthSpinBox = new QSpinBox;
    QSpinBox *thumbnailHeightSpinBox = new QSpinBox;
    thumbnailWidthSpinBox->setMinimum(0);
    thumbnailWidthSpinBox->setMaximum(999);


    QLabel *jpegQualityLabel = new QLabel("Jpeg Quality");
    QSlider *jpegQualitySlider = new QSlider(Qt::Horizontal);
    QSpinBox *jpegQualitySpinBox = new QSpinBox;
    jpegQualitySpinBox->setMinimum(0);
    jpegQualitySpinBox->setMaximum(100);

    QGridLayout *thumbnailLayout = new QGridLayout;

    thumbnailLayout->addWidget(thumbnailWidthLabel,0,0);
    thumbnailLayout->addWidget(thumbnailHeightLabel,1,0);
    thumbnailLayout->addWidget(thumbnailWidthSpinBox,0,1);
    thumbnailLayout->addWidget(thumbnailHeightSpinBox,1,1);
//    thumbnailLayout->addItem(new QSpacerItem(0,0),0,2);

    thumbnailLayout->setColumnStretch(0,0);
    thumbnailLayout->setColumnStretch(1,0);
    thumbnailLayout->setColumnStretch(2,1);

    thumbnailLayout->addWidget(jpegQualityLabel,2,0);
    thumbnailLayout->addWidget(jpegQualitySlider,2,1,1,2);
    thumbnailLayout->addWidget(jpegQualitySpinBox,2,3);
//    thumbnailLayout->addItem(new QSpacerItem(0,0),3,0);

    thumbnailLayout->setRowStretch(0,0);
    thumbnailLayout->setRowStretch(1,0);
    thumbnailLayout->setRowStretch(2,0);
    thumbnailLayout->setRowStretch(3,1);

    thumbnailSettingGrp->setLayout(thumbnailLayout);

    return thumbnailSettingGrp;

}

QGroupBox *RenderSettingTab::createJpegProxySetting()
{
    QGroupBox *jpegProxyGrp = new QGroupBox("Jpeg Proxy Setting");
    jpegProxyGrp->setCheckable(true);
    jpegProxyGrp->setChecked(true);

    QGroupBox *jpegSize = new QGroupBox("Custom Size");
    jpegSize->setCheckable(true);
    jpegSize->setChecked(false);

    QLabel *proxyWidthLabel = new QLabel("Width Size : ");
    QLabel *proxyHeightLabel = new QLabel("Height Size : ");

    QSpinBox *proxyWidthSpinBox = new QSpinBox;
    proxyWidthSpinBox->setMinimum(0);
    proxyWidthSpinBox->setMaximum(9999);

    QSpinBox *proxyHeightSpinBox = new QSpinBox;
    proxyHeightSpinBox->setMinimum(0);
    proxyHeightSpinBox->setMaximum(9999);

   QGridLayout *proxySizeLayout = new QGridLayout;

    proxySizeLayout->addWidget(proxyWidthLabel,0,0);
    proxySizeLayout->addWidget(proxyHeightLabel,1,0);

    proxySizeLayout->addWidget(proxyWidthSpinBox,0,1);
    proxySizeLayout->addWidget(proxyHeightSpinBox,1,1);

    jpegSize->setLayout(proxySizeLayout);

    QGridLayout *proxyLayout = new QGridLayout;

    QLabel *proxyQualityLabel = new QLabel("Jpeg Quality");
    QSlider *proxyQualitySlider = new QSlider(Qt::Horizontal);
    QSpinBox *proxyQualitySpinBox = new QSpinBox;
    proxyQualitySpinBox->setMinimum(0);
    proxyQualitySpinBox->setMaximum(100);

    QLabel *proxyColorspaceLabel = new QLabel("Output ColorSpace : ");
    QComboBox *proxyColorspaceCombo = new QComboBox;
    proxyColorspaceCombo->addItem("sRGB(default)");
    proxyColorspaceCombo->addItem("RRT(sRGB)");
    proxyColorspaceCombo->addItem("RRT(rec709)");


    proxyLayout->addWidget(jpegSize,0,0,1,2);
//    proxyLayout->addItem(new QSpacerItem(0,0),0,2);

    proxyLayout->setColumnStretch(0,0);
    proxyLayout->setColumnStretch(1,0);
    proxyLayout->setColumnStretch(2,1);

    proxyLayout->addWidget(proxyQualityLabel,1,0);
    proxyLayout->addWidget(proxyQualitySlider,1,1,1,2);
    proxyLayout->addWidget(proxyQualitySpinBox,1,3);
    proxyLayout->addWidget(proxyColorspaceLabel,2,0);
    proxyLayout->addWidget(proxyColorspaceCombo,2,1);
//    proxyLayout->addItem(new QSpacerItem(0,0),2,0);

    proxyLayout->setRowStretch(0,0);
    proxyLayout->setRowStretch(1,0);
    proxyLayout->setRowStretch(3,1);

    jpegProxyGrp->setLayout(proxyLayout);


    return jpegProxyGrp;
}

QGroupBox *RenderSettingTab::createTacticdbSetting()
{
    QGroupBox *tacticDBGrp = new QGroupBox("Tactic DB Setting");
    tacticDBGrp->setCheckable(true);
    tacticDBGrp->setChecked(true);

    QLabel *tacticLabel = new QLabel("Tactic DB Address : ");
    QLineEdit *tacticEdit = new QLineEdit("192.168.100.100");

    QPushButton *connectTestBtn = new QPushButton("Connect Test");

    QGridLayout *tacticLayout = new QGridLayout;

    tacticLayout->addWidget(tacticLabel,0,0);
    tacticLayout->addWidget(tacticEdit,0,1,1,2);
    tacticLayout->addWidget(connectTestBtn,1,2);
    tacticLayout->addItem(new QSpacerItem(0,0),2,0);

    tacticLayout->setRowStretch(0,0);
    tacticLayout->setRowStretch(1,0);
    tacticLayout->setRowStretch(2,1);

    tacticDBGrp->setLayout(tacticLayout);

    return tacticDBGrp;
}

QGroupBox *RenderSettingTab::createQuickMovSetting()
{
    QGroupBox *quicktimeMovGrp = new QGroupBox("QuickTime Mov Setting");
    quicktimeMovGrp->setCheckable(true);
    quicktimeMovGrp->setChecked(true);

    QLabel *quicktimeMovWidthLabel = new QLabel("Width Size : ");
    QLabel *quicktimeMovHeightLabel = new QLabel("Height Size : ");
    QLabel *quicktimeMovColorspaceLabel = new QLabel("Output ColorSpace : ");
    QLabel *quicktimeMovCodecLabel= new QLabel("Output Codec : ");
    QLabel *quicktimeMovFrameRateLabel= new QLabel("Output FrameRate : ");

    QSpinBox *quicktimeMovWidthSpinBox = new QSpinBox;
    QSpinBox *quicktimeMovHeightSpinBox = new QSpinBox;

    QComboBox *quicktimeMovColorspaceCombo = new QComboBox;
    quicktimeMovColorspaceCombo->addItem("sRGB(default)");
    quicktimeMovColorspaceCombo->addItem("RRT(sRGB)");
    quicktimeMovColorspaceCombo->addItem("RRT(rec709)");

    QComboBox *quicktimeMovCodecCombo = new QComboBox;
    quicktimeMovCodecCombo->addItem("ProRess422 HQ");
    quicktimeMovCodecCombo->addItem("ProRess422 LT");
    quicktimeMovCodecCombo->addItem("ProRess422 Proxy");
    quicktimeMovCodecCombo->addItem("H264");

    QComboBox *quicktimeMovFrameRateCombo = new QComboBox;
    quicktimeMovFrameRateCombo->addItem("23.976");
    quicktimeMovFrameRateCombo->addItem("24");
    quicktimeMovFrameRateCombo->addItem("25");
    quicktimeMovFrameRateCombo->addItem("29.97");
    quicktimeMovFrameRateCombo->addItem("30");

    QGridLayout *quicktimeMovLayout = new QGridLayout;

    quicktimeMovLayout->addWidget(quicktimeMovWidthLabel,0,0);
    quicktimeMovLayout->addWidget(quicktimeMovHeightLabel,1,0);
    quicktimeMovLayout->addWidget(quicktimeMovWidthSpinBox,0,1);
    quicktimeMovLayout->addWidget(quicktimeMovHeightSpinBox,1,1);
    quicktimeMovLayout->addWidget(quicktimeMovColorspaceLabel,2,0);
    quicktimeMovLayout->addWidget(quicktimeMovColorspaceCombo,2,1,1,2);
    quicktimeMovLayout->addWidget(quicktimeMovCodecLabel,3,0);
    quicktimeMovLayout->addWidget(quicktimeMovCodecCombo,3,1,1,2);
    quicktimeMovLayout->addWidget(quicktimeMovFrameRateLabel,4,0);
    quicktimeMovLayout->addWidget(quicktimeMovFrameRateCombo,4,1,1,2);

    quicktimeMovLayout->setColumnStretch(0,0);
    quicktimeMovLayout->setColumnStretch(1,0);
    quicktimeMovLayout->setColumnStretch(2,0);
    quicktimeMovLayout->setColumnStretch(3,1);

    quicktimeMovLayout->setRowStretch(0,0);
    quicktimeMovLayout->setRowStretch(5,1);


    quicktimeMovGrp->setLayout(quicktimeMovLayout);

    return quicktimeMovGrp;
}
