#ifndef RENDERSETTINGTAB_H
#define RENDERSETTINGTAB_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>

class RenderSettingTab : public QWidget
{
    Q_OBJECT
public:
    explicit RenderSettingTab(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *mainLayout;
    QGroupBox *createThumbnailSetting();
    QGroupBox *createJpegProxySetting();
    QGroupBox *createTacticdbSetting();
    QGroupBox *createQuickMovSetting();
};

#endif // RENDERSETTINGTAB_H
