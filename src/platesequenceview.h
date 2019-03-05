#ifndef PLATESEQUENCEVIEW_H
#define PLATESEQUENCEVIEW_H

#include <QTableView>
#include <QAction>

class PlateSequenceView : public QTableView
{
    Q_OBJECT
public:
    PlateSequenceView(QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void itemUp();
    void itemDown();


private:
    QAction *removeSelectedAct;
    QAction *itemUpAct;
    QAction *itemDownAct;
    QAction *singleDataInputAct;
    QAction *sequentialDataInputAct;
    int contextPos;

private slots:
    void testFunc();
    void removeSelected();
    void singleDataInput();
    void sequentialDataInput();
};

#endif // PLATESEQUENCEVIEW_H
