#ifndef DIRSETTINGTAB_H
#define DIRSETTINGTAB_H

#include <QWidget>
#include <QTreeView>
#include "templateview.h"
#include "pathpreview.h"
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>

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
    void setRenumber(bool check);
    void setStartNum(int value);
    void setDigitNum(int value);

private:
    TemplateView *templateView;
    PathPreView *preView;
    QWidget *propertyView;
    QStandardItem *currentItem;
    QComboBox *typeCombo;
    QGroupBox *renumberGrp;
    QSpinBox *startNumEdit;
    QSpinBox *digitNumEdit;
};

#endif // DIRSETTINGTAB_H
