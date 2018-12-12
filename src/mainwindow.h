#ifndef SATURN_H
#define SATURN_H

#include <QMainWindow>

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    QTabWidget *tab;
};

#endif // SATURN_H
