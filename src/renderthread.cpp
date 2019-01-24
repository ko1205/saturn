#include "renderthread.h"
#include <QDebug>

RenderThread::RenderThread(QObject *parent)
    :QThread(parent)
{

}

void RenderThread::run()
{
    status = true;
    int plateListCount = plateListModel->rowCount();
    int templateFileCount = templateView->getFileCount();
    int processCount = plateListCount*templateFileCount;
    emit renderStart(processCount);
    for(int i = 0; i < plateListCount;i++)
    {

    }

    qDebug() << "render Thread run";
    qDebug() << plateListCount;
    qDebug() << templateFileCount;
    qDebug() << processCount;
}

void RenderThread::setPlateListModel(QAbstractItemModel *model)
{
    plateListModel = model;

}

void RenderThread::setTemplateModel(QStandardItemModel *model)
{
    templateModel = model;
}

void RenderThread::setTemplateView(TemplateView *view)
{
    templateView = view;

}

void RenderThread::setRenderSetting(RenderSettingTab *settingTab)
{
    renderSetting = settingTab;
}
