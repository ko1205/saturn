#ifndef PLATELISTTAB_H
#define PLATELISTTAB_H

#include <QWidget>
#include "dirselector.h"
#include "plateviewcontroller.h"
#include "searchthread.h"

class PlateListTab : public QWidget
{
    Q_OBJECT
public:
    PlateListTab(QWidget *parent = 0);

signals:
    void searchingDir(QString dir);
    void searchFinish(bool finish);

public slots:
    void searchPlate(QString path);
    void searchCancel();


private:
    void searchPlateLoop(QString path);

    DirSelector *dirSelector;
    PlateViewController *plateViewController;
    SearchThread *searchThread;
};

#endif // PLATELISTTAB_H
