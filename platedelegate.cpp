#include "platedelegate.h"
#include <QPainter>
#include <QModelIndex>
#include <QComboBox>

PlateDelegate::PlateDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void PlateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QPixmap test(100,100);
//    QColor black(50,50,50);
//    test.fill(black);
    if(index.column()==0){
        painter->save();
        QPixmap test;
        test.load("/Users/ko1205/Dev/saturn_project/test_images/A193_C003_0704V4_289/JPEG/A193_C003_0704V4.0000289.jpg");
        int w = option.rect.width()/2;
        int h = option.rect.height()/2;

        painter->drawPixmap(option.rect,test);
//        painter->drawPixmap(option.rect.left(),option.rect.top(),100,100,test);

    //    painter->drawText(option.rect,"test_text");
    //    QStyledItemDelegate::paint(painter,option,index);
        painter->restore();
    }else{
        QStyledItemDelegate::paint(painter,option,index);
    }

}

QSize PlateDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if(index.column()==0)
//    {
//        QSize test(3000,500);

//        return test;
//    }
/*!
  실제 최종 size 결정에 대한 부분은 Delegate::sizeHint() 에서 결정됨
  model->data(Qt::SizeHintRole)에서 지정한 값은 결국 Delegate 에서 받아서 최종 View로 전송
  Treview에서는 바로 적용 TableView에서는 resizeColumnsToContents(), resizeRowsToContents()
  두 함수를 호출해야 적용됨.
 */
    return index.data(Qt::SizeHintRole).toSize();
//    return QStyledItemDelegate::sizeHint(option,index);
}

QWidget *PlateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QWidget *test = new QWidget(parent);
    QComboBox *test = new QComboBox(parent);
    test->addItem("test1");
    test->addItem("test2");
    return test;
}
