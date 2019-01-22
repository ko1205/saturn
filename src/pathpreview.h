#ifndef PATHPREVIEW_H
#define PATHPREVIEW_H

#include <QTreeView>
#include <QStandardItemModel>

class PathPreView : public QTreeView
{
    Q_OBJECT
public:
    PathPreView(QWidget *parent=0);
    void setTemplateModel(QAbstractItemModel *model);
    void setPlateListModel(QAbstractItemModel *model);
    void updatePrevew();

private:
    void createIcon();
    void createRootFolder();
    QStandardItem  *readTemplateViewLoop(QModelIndex &index,QModelIndex &previewIndex,QStandardItem *parentItem = 0, int deepth = 0);
    QString replaceName(QStandardItem *item, int num);
    QStandardItem *testFunc(int num,QStandardItem *templateItem,QStandardItem *preViewParentItem = 0);
    QStandardItemModel *preViewModel;
    QStandardItemModel *templateModel;
    QIcon folderIcon;
    QIcon fileIcon;
    QStandardItem *rootItem;

    QAbstractItemModel *plateListModel;
};

#endif // PATHPREVIEW_H
