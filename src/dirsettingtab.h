#ifndef DIRSETTINGTAB_H
#define DIRSETTINGTAB_H

#include <QWidget>
#include <QTreeView>
#include "templateview.h"

class DirSettingTab : public QWidget
{
    Q_OBJECT
public:
    DirSettingTab(QWidget *parent = 0);

signals:

public slots:

private:
    TemplateView *templateView;
    QTreeView *preView;
    QWidget *propertyView;
};

#endif // DIRSETTINGTAB_H
