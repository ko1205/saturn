#ifndef TEMPLATEVIEW_H
#define TEMPLATEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

class TemplateView : public QTreeView
{
    Q_OBJECT
public:
    TemplateView(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void insertFolder();
    void deleteFolder();
    void setRootFolderName();

private:
    void createIcon();
    void createRootFolder();
    QStandardItemModel *templateModel;
    QStandardItem *rootItem;

    QMenu *popupMenu;
    QAction *insertFolderAct;

    QIcon folderIcon;
    QIcon fileIcon;

};

#endif // TEMPLATEVIEW_H
