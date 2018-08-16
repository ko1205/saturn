#ifndef MAINCENTRALWIDGET_H
#define MAINCENTRALWIDGET_H

#include <QWidget>

class QMdiArea;

class MainCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainCentralWidget(QWidget *parent = 0);
    void creatSubWindow();

private:
    void createLayout();
    QMdiArea *m_mdiArea;

signals:

public slots:
};

#endif // CENTRALWIDGET_H
