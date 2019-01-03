#ifndef PLATEVIEWCONTROLLER_H
#define PLATEVIEWCONTROLLER_H

#include <QWidget>
#include <QTableView>
#include "plateitemmodel.h"

class PlateViewController : public QWidget
{
    Q_OBJECT
public:
    PlateViewController(QWidget *parent = 0);
    void findedSequence(PlateItem item);
    int oldScrollMax;

signals:

public slots:
    void rowResiz(int index, int oldSize, int newSize);
    void autoScroll(int min,int max);

private:
    QTableView *plateSequenceView;
    PlateItemModel *model;

};

#endif // PLATEVIEWCONTROLLR_H
