#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include <QAbstractItemModel>
#include "rendersettingtab.h"
#include <QStandardItemModel>
#include "templateview.h"
#include "plateitemmodel.h"

class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(QObject *parent = 0);
    void setPlateListModel(QAbstractItemModel *model);
    void setTemplateModel(QStandardItemModel *model);
    void setTemplateView(TemplateView *view);
    void setRenderSetting(RenderSettingTab *settingTab);

signals:
    void renderStart(int processCount);
    void processDone();

public slots:
    void setTargetPath(QDir path);

protected:
    void run();

private:
    void readTemplateLoop(QModelIndex index,QDir path);
    QString replaceName(QString name);
    void sequenceFileCopy(QStandardItem *item,QDir path,QString targetName);
    void makeThumbnail(QDir path,QString targetName);
    void makeJpegProxy(QStandardItem *item, QDir path,QString targetName);
    void makePreviewMov(QDir path, QString targetName);
    QImage loadImage(QFileInfo file);
    QString replaceOrgName(QString filename,int num, int pendingCount);
    PlateItemModel *plateListModel;
    RenderSettingTab *renderSetting;
    QStandardItemModel *templateModel;
    TemplateView *templateView;
    bool status;
    QDir targetPath;
    PlateItem *currentItem;
};

#endif // RENDERTHREAD_H
