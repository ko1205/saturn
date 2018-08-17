#ifndef PLATEMAINVIEW_H
#define PLATEMAINVIEW_H

//#include <QWidget>
#include <QListView>

class PlateMainView : public QListView
{
    Q_OBJECT
public:
    explicit PlateMainView(QWidget *parent = 0);

signals:

public slots:
};

#endif // PLATEMAINVIEW_H
