#ifndef PLATEVIEWDELEGATE_H
#define PLATEVIEWDELEGATE_H

#include <QStyledItemDelegate>

class PlateViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    PlateViewDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PLATEVIEWDELEGATE_H
