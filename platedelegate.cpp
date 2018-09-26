#include "platedelegate.h"
#include <QPainter>

PlateDelegate::PlateDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void PlateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QPixmap test(100,100);
//    QColor black(50,50,50);
//    test.fill(black);
    painter->save();
    QPixmap test;
    test.load("/Users/ko1205/Dev/saturn_project/test_images/A193_C003_0704V4_289/JPEG/A193_C003_0704V4.0000289.jpg");
    int w = option.rect.width()/2;
    int h = option.rect.height()/2;

//    painter->drawPixmap(option.rect,test);
    painter->drawPixmap(option.rect.left(),option.rect.top(),100,100,test);

//    painter->drawText(option.rect,"test_text");
//    QStyledItemDelegate::paint(painter,option,index);
    painter->restore();

}

QSize PlateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if(index.column()==0)
//    {
//        QSize test(3000,500);

//        return test;
//    }
    return QStyledItemDelegate::sizeHint(option,index);
}
