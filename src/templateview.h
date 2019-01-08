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
    void newFileSlot();
    void setRootFolderName();

private:
    void createIcon();
    void createRootFolder();
    int checkSameName(QString name,bool isFolder,const QModelIndex &parent);
    QString autoRename(QString name,bool isFolder,const QModelIndex &parent,int count = 0);

    QStandardItemModel *templateModel;
    QStandardItem *rootItem;

    QMenu *popupMenu;
    QAction *insertFolderAct;
    QAction *newFile;

    QIcon folderIcon;
    QIcon fileIcon;

    QString oldName;

private slots:
    void storOldName(const QModelIndex &index);
    void checkRename(const QModelIndex &index);

};

#endif // TEMPLATEVIEW_H
