#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainCentralWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenuBar();
    void createAction();

    MainCentralWidget *m_centralWidget;
};

#endif // MAINWINDOW_H
