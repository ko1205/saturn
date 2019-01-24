#include "renderthread.h"
#include <QDebug>

RenderThread::RenderThread(QObject *parent)
    :QThread(parent)
{

}

void RenderThread::run()
{
    qDebug() << "render Thread run";
    qDebug() << plateListModel->rowCount();
    qDebug() << templateModel->rowCount();
    qDebug() << templateView->getFileCount();
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
