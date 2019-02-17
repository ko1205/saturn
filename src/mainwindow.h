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
//    QTabWidget *tab;
    void createAction();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *saveTemplateAct;
    QAction *deleteTemplateAct;
    QAction *exportTemplateAct;
    QAction *importTemplateAct;
};

#endif // SATURN_H
