#ifndef PLATESEQUENCEVIEW_H
#define PLATESEQUENCEVIEW_H

#include <QTableView>
#include <QAction>
#include <QDialog>
#include <QSpinBox>

class SequenceNameInputDialog : public QDialog
{
    Q_OBJECT
public:
    SequenceNameInputDialog(QWidget *parent = nullptr);
    ~SequenceNameInputDialog();

signals:
    void sendeValue(QString value,int start,int stap);

private:
    QLineEdit * valueEdit;
    QSpinBox * startNumSpin;
    QSpinBox * stapNumSpin;

private slots:
    void acceptValue();
};

class PlateSequenceView : public QTableView
{
    Q_OBJECT
public:
    PlateSequenceView(QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void itemUp();
    void itemDown();
    void writeSequenceValue(QString valueText,int startNum,int stapNum);


private:
    QAction *removeSelectedAct;
    QAction *itemUpAct;
    QAction *itemDownAct;
    QAction *singleDataInputAct;
    QAction *sequentialDataInputAct;
    int contextPos;

    bool isValidSelected(QModelIndexList &list);

private slots:
    void testFunc();
    void removeSelected();
    void singleDataInput();
    void sequentialDataInput();
};

#endif // PLATESEQUENCEVIEW_H
