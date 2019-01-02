#include "plateviewdelegate.h"

PlateViewDelegate::PlateViewDelegate()
{

}

void PlateViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::paint(painter,option,index);
}
