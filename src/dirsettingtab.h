#ifndef DIRSETTINGTAB_H
#define DIRSETTINGTAB_H

#include <QWidget>
#include <QTreeView>
#include "templateview.h"
#include "pathpreview.h"
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QPushButton>
#include <QDir>

class DirSettingTab : public QWidget
{
    Q_OBJECT
public:
    DirSettingTab(QWidget *parent = 0);
    void setPlateLIstModel(QAbstractItemModel* model);
    QStandardItemModel *getTemplateModel();
    TemplateView *getTemplateView();

signals:
    void setTargetPath(QDir path);

public slots:
    void connectItem(QStandardItem *item);
    void changeType(int index);
    void setRenumber(bool check);
    void setStartNum(int value);
    void setDigitNum(int value);
    void selectDir();

private:
    TemplateView *templateView;
    PathPreView *preView;
    QWidget *propertyView;
    QStandardItem *currentItem;
    QComboBox *typeCombo;
    QGroupBox *renumberGrp;
    QSpinBox *startNumEdit;
    QSpinBox *digitNumEdit;
    QLineEdit *targetPathEdit;
    QPushButton *targetPathButton;
};

#endif // DIRSETTINGTAB_H
