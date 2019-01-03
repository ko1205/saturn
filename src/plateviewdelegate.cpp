#include "plateviewdelegate.h"
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QLabel>
#include <QApplication>

PlateViewDelegate::PlateViewDelegate()
{

}

void PlateViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0){
        QImage image = qvariant_cast<QImage>(index.data(Qt::DecorationRole));

        painter->save();
        int w = option.rect.width();
        int h = option.rect.height();
        QSize cellSize(w,h);
        image = image.scaled(cellSize,Qt::KeepAspectRatio);

        int imageMarginWidth = ((w - image.width())/2);
        int imageMarginHeight = ((h - image.height())/2);

        painter->drawPixmap(option.rect.left()+imageMarginWidth,option.rect.top()+imageMarginHeight,image.width(),image.height(),QPixmap::fromImage(image));
        //        painter->drawPixmap(option.rect.left(),option.rect.top(),100,100,test);

        //    painter->drawText(option.rect,"test_text");
        //    QStyledItemDelegate::paint(painter,option,index);
        painter->restore();
    }else if(index.column() == 2){
        QString frameInfo;
        QPair<long long,long long> frame = qvariant_cast<QPair<long long,long long>>(index.data());
        if(frame.first !=frame.second)
        {
            frameInfo =displayText( QString("start : %1\n\nEnd : %2\n\nDuration : %3").arg(QString::number(frame.first),QString::number(frame.second),QString::number(frame.second-frame.first+1)),option.locale);
//            frameInfo =QString("start : %1\n\nEnd : %2\n\nDuration : %3").arg(QString::number(frame.first),QString::number(frame.second),QString::number(frame.second-frame.first+1));
        }else{
            frameInfo = "Still image";
        }
        QStyleOptionViewItem opt = option;
        opt.text = frameInfo;
//        const QWidget *widget = option.widget;
//        QStyle *style = widget->style();
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);
    }else{

        return QStyledItemDelegate::paint(painter,option,index);
    }
}
