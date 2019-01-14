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

private:
    void createIcon();
    void createRootFolder();
    void readTemplateView();
    QStandardItemModel *preViewModel;
    QStandardItemModel *templateModel;
    QIcon folderIcon;
    QIcon fileIcon;
    QStandardItem *rootItem;
};

#endif // PATHPREVIEW_H
