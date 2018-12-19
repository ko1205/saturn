#ifndef PLATELISTTAB_H
#define PLATELISTTAB_H

#include <QWidget>
#include "dirselector.h"
#include "plateviewcontroller.h"

class PlateListTab : public QWidget
{
    Q_OBJECT
public:
    PlateListTab(QWidget *parent = 0);

signals:

public slots:

private:
    DirSelector *dirSelector;
    PlateViewController *plateViewController;

};

#endif // PLATELISTTAB_H
