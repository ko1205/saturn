#ifndef DIRSETTINGTAB_H
#define DIRSETTINGTAB_H

#include <QWidget>
#include <QTreeView>
#include "templateview.h"
#include "pathpreview.h"

class DirSettingTab : public QWidget
{
    Q_OBJECT
public:
    DirSettingTab(QWidget *parent = 0);

signals:

public slots:

private:
    TemplateView *templateView;
    PathPreView *preView;
    QWidget *propertyView;
};

#endif // DIRSETTINGTAB_H
