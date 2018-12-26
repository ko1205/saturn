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

signals:

public slots:
    void findedSequence(QString path);

private:
    QTableView *plateSequenceView;
    PlateItemModel *model;

};

#endif // PLATEVIEWCONTROLLR_H
