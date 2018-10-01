#include "platedatamodel.h"
#include <QSize>
#include <QDebug>

PlateItem::PlateItem(sequenceInfo &info)
{
    this->filePath = info.sequenceName;
    this->frameRange.first = info.startFrame;
    this->frameRange.second = info.endFrame;
}

QVariant PlateItem::data(const QModelIndex &index) const
{
    int col = index.column();
    switch (col) {
    case 1:
        return this->filePath;
        break;
    case 2:
        return this->frameRange.first;
        break;
    case 3:
        return this->frameRange.second;
    default:
        return QVariant();
        break;
    }
}

PlateDataModel::PlateDataModel(QObject *parent)
    :QAbstractItemModel(parent)
{
//    PlateItem tmp;
//
//    plateItem.append(tmp);
}

QVariant PlateDataModel::data(const QModelIndex &index, int role) const
{
/*!
  실제 최종 size 결정에 대한 부분은 Delegate::sizeHint() 에서 결정됨
  model->data(Qt::SizeHintRole)에서 지정한 값은 결국 Delegate 에서 받아서 최종 View로 전송
  Treview에서는 바로 적용 TableView에서는 resizeColumnsToContents(), resizeRowsToContents()
  두 함수를 호출해야 적용됨.
 */
    if(role == Qt::DisplayRole||role==Qt::EditRole){
        return plateItem[index.row()].data(index);
    }else if(role==Qt::SizeHintRole){
        return QSize(300,100);
    }else{
        return QVariant();
    }
}

QModelIndex PlateDataModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

QModelIndex PlateDataModel::parent(const QModelIndex &child) const
{
/*!
 Tree구조로 사용하지 않을 예정 parent는 항상 rootIndex
*/
    return QModelIndex();
}

int PlateDataModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << plateItem.count();
    return plateItem.count();
}

int PlateDataModel::columnCount(const QModelIndex &parent) const
{
    return 10;
}

bool PlateDataModel::hasChildren(const QModelIndex &parent) const
{
/*!
    TreeView 일경우에만 작동
    TableView일경우에는 children 이 의미가 없음
*/
    if(parent == QModelIndex())
    {
        return true;
    }else{
        return false;
    }
}

//bool PlateDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    return true;
//}

Qt::ItemFlags PlateDataModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0){
    return Qt::ItemIsSelectable
            |Qt::ItemIsEnabled
            |Qt::ItemIsEditable
            |Qt::ItemIsDragEnabled
            |Qt::ItemIsDropEnabled;
    }else{
        return Qt::ItemIsSelectable
                |Qt::ItemIsEnabled
                |Qt::ItemIsEditable
                |Qt::ItemIsDragEnabled
                |Qt::ItemIsDropEnabled;
    }
//    return Qt::ItemIsEditable;
}

QVariant PlateDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return "Thumnail";
        case 1:
            return "Druation";
        case 2:
            return "path";
        }

        return QStringLiteral("Column %1").arg(section);
    }else{
        return section+1;
    }
}

bool PlateDataModel::appendItem(sequenceInfo &item)
{
    PlateItem temp(item);
    plateItem.append(temp);

/*!
  기본 값에서 모델에 데이터를 추가해도 view에서 신호를 받지 않는다.
  아래 두함수를 통해 private클래스내부에 Signal이 정의되어 있고
  아직 정확한 이해는 안되지만 model 부분에 데이터가 추가 되면 아래 함수를 호출해주어야한다.
  두개가 쌍으로 호출되지 않으면 프로그램이 죽어버린다.
*/
    beginInsertRows(QModelIndex(),0,0);
    endInsertRows();

    return true;
}



