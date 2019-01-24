#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include <QAbstractItemModel>
#include "rendersettingtab.h"
#include <QStandardItemModel>
#include "templateview.h"

class RenderThread : public QThread
{
public:
    RenderThread(QObject *parent = 0);
    void setPlateListModel(QAbstractItemModel *model);
    void setTemplateModel(QStandardItemModel *model);
    void setTemplateView(TemplateView *view);
    void setRenderSetting(RenderSettingTab *settingTab);

signals:
    void renderStart(int processCount);

protected:
    void run();

private:
    QAbstractItemModel *plateListModel;
    RenderSettingTab *renderSetting;
    QStandardItemModel *templateModel;
    TemplateView *templateView;
};

#endif // RENDERTHREAD_H
