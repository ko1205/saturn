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
    QMenu *fileMenu;

    QToolBar *fileToolbar;

    QAction *newAct;

    MainCentralWidget *m_centralWidget;

    void createMenuBar();
    void createToolbar();
    void createAction();

private slots:
    bool newProject();

};

#endif // MAINWINDOW_H
