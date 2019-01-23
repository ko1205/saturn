#ifndef DIRSETTINGTAB_H
#define DIRSETTINGTAB_H

#include <QWidget>
#include <QTreeView>
#include "templateview.h"
#include "pathpreview.h"
#include <QComboBox>

class DirSettingTab : public QWidget
{
    Q_OBJECT
public:
    DirSettingTab(QWidget *parent = 0);
    void setPlateLIstModel(QAbstractItemModel* model);

signals:

public slots:
    void connectItem(QStandardItem *item);
    void changeType(int index);


private:
    TemplateView *templateView;
    PathPreView *preView;
    QWidget *propertyView;
    QStandardItem *currentItem;
    QComboBox *typeCombo;
};

#endif // DIRSETTINGTAB_H
