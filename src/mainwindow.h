#ifndef SATURN_H
#define SATURN_H

#include <QMainWindow>
#include "centralwidget.h"
#include <QDialog>
#include <QListWidget>

class DeleteTemplateDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteTemplateDialog(QWidget *parent = nullptr);
    ~DeleteTemplateDialog();
    void setTemplateList(QStringList list,QComboBox *combobox);

signals:
    void clickDelete(QString name);

private:
    QListWidget *templateList;
    QPushButton *deleteButton;
    QPushButton *cancelButton;
    QComboBox *templateListComboIns;

private slots:
    void deleteTemplate();
};

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
