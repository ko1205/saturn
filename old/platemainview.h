#ifndef PLATEMAINVIEW_H
#define PLATEMAINVIEW_H

//#include <QWidget>
//#include <QListView>
#include <QTableView>
#include <QTreeView>

class PlateMainView : public QTableView
{
    Q_OBJECT
public:
    explicit PlateMainView(QWidget *parent = 0);

signals:

public slots:
};

#endif // PLATEMAINVIEW_H
