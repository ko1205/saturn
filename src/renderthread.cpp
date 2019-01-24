#include "renderthread.h"
#include <QDebug>
#include <Python.h>

RenderThread::RenderThread(QObject *parent)
    :QThread(parent)
{
//    Py_Initialize();

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
    plateListModel = qobject_cast<PlateItemModel*>(model);
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
