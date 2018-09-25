#include "platedatamodel.h"

PlateItem::PlateItem()
{
    this->filePath = "testPath/Path/Path";
    this->frameRange.first = 10;
    this->frameRange.second = 100;
}

QVariant PlateItem::data(const QModelIndex &index) const
{
    int col = index.column();
    switch (col) {
    case 0:
        return this->filePath;
        break;
    case 1:
        return this->frameRange.first;
        break;
    case 2:
        return this->frameRange.second;
    default:
        return QVariant();
        break;
    }
}

PlateDataModel::PlateDataModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    PlateItem tmp;

    plateItem.append(tmp);
}

QVariant PlateDataModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole||role==Qt::EditRole){
        return plateItem.at(0).data(index);
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
    return 5;
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



