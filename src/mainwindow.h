#ifndef SATURN_H
#define SATURN_H

#include <QMainWindow>
#include "centralwidget.h"

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

    CentralWidget *centralwidget;

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *saveTemplateAct;
    QAction *deleteTemplateAct;
    QAction *importTemplateAct;
    QAction *exportTemplateAct;

private slots:
    void saveTemplate();
    void deleteTemplate();
    void importTemplate();
    void exportTemplate();
};

#endif // SATURN_H
