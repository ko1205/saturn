#include "platedatamodel.h"

PlateDataModel::PlateDataModel(QObject *parent)
    :QAbstractItemModel(parent)
{

}

QVariant PlateDataModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
        return "test";
    else
        return QVariant();

}

QModelIndex PlateDataModel::index(int row, int column, const QModelIndex &parent) const
{
//    int *test;
    return createIndex(row, column);
}

QModelIndex PlateDataModel::parent(const QModelIndex &child) const
{
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
    return Qt::ItemIsSelectable
            |Qt::ItemIsEnabled
            |Qt::ItemIsEditable
            |Qt::ItemIsDragEnabled
            |Qt::ItemIsDropEnabled;
//    return Qt::ItemIsEditable;
}



