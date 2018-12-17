#ifndef PLATEVIEWCONTROLLER_H
#define PLATEVIEWCONTROLLER_H

#include <QWidget>
#include <QTableView>

class PlateViewController : public QWidget
{
    Q_OBJECT
public:
    PlateViewController(QWidget *parent = 0);

signals:

public slots:

private:
    QTableView *plateSequenceView;

};

#endif // PLATEVIEWCONTROLLR_H
