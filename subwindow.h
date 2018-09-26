#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

class PlateMainView;
class PlateDataModel;
class PlateDelegate;

class SubWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SubWindow(QWidget *parent = 0);

private:
    void initWindow();
    PlateDelegate *plateDelegate;
    PlateMainView *plateMainView;
    PlateDataModel *plateDataModel;

signals:

public slots:
};

#endif // SUBWINDOW_H
