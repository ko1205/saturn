#ifndef SETURNCENTRALWIDGET_H
#define SETURNCENTRALWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

class QMdiArea;

class SeturnCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SeturnCentralWidget(QWidget *parent = 0);

private:
    QMdiArea *m_mdiArea;

signals:

public slots:
};

#endif // CENTRALWIDGET_H
