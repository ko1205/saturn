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

private:
    QAction *mulitValueAct;
    int contextPos;

private slots:
    void testFunc();

};

#endif // PLATESEQUENCEVIEW_H
