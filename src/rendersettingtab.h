#ifndef RENDERSETTINGTAB_H
#define RENDERSETTINGTAB_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QSlider>

class RenderSettingTab : public QWidget
{
    Q_OBJECT
public:
    explicit RenderSettingTab(QWidget *parent = 0);
    int getThumbnailWidth();
    int getThumbnailHeight();
    int getThumbnailQuality();

signals:

public slots:

private:
    QGridLayout *mainLayout;
    QGroupBox *createThumbnailSetting();
    QGroupBox *createJpegProxySetting();
    QGroupBox *createTacticdbSetting();
    QGroupBox *createQuickMovSetting();

    QSpinBox *thumbnailWidthSpinBox;
    QSpinBox *thumbnailHeightSpinBox;
    QSlider *thumbnailJpegQualitySlider;
};

#endif // RENDERSETTINGTAB_H
