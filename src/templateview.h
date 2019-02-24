#ifndef TEMPLATEVIEW_H
#define TEMPLATEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include "pathpreview.h"
#include <QDir>

class TemplateView : public QTreeView
{
    Q_OBJECT
public:
    TemplateView(QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event) override;
    void setPathPreview(PathPreView *preview);
    int getFileCount();
    QStandardItem *root();
    void refreshPreView();
    QIcon folderIconOut();
    QIcon fileIconOut();
    void addFileCount();

signals:
    void itemClickedView(QStandardItem *item);

public slots:
    void insertFolder();
    void deleteFolder();
    void newFileSlot();
    void resetTemplate();
    void setRootFolderName(QDir path);

private:
    void createIcon();
    void createRootFolder();
    int checkSameName(QString name,int isFolder,const QModelIndex &parent);
    QString autoRename(QString name,int isFolder,const QModelIndex &parent,int count = 0);
    int countChildFile(QStandardItem *item);

    QStandardItemModel *templateModel;
    QStandardItem *rootItem;

    QMenu *popupMenu;
    QAction *insertFolderAct;
    QAction *newFile;
    QAction *deleteAct;
    QAction *deleteAllAct;

    QIcon folderIcon;
    QIcon fileIcon;

    QString oldName;
    PathPreView *pathPreviewIns;
    int fileCount;

private slots:
    void storOldName(const QModelIndex &index);
    void checkRename(const QModelIndex &index);
    void setinfo(const QModelIndex &index);
};

#endif // TEMPLATEVIEW_H
