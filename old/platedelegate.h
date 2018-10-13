#ifndef PLATEDELEGATE_H
#define PLATEDELEGATE_H

#include <QStyledItemDelegate>

class PlateDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    PlateDelegate(QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PLATEDELEGATE_H
