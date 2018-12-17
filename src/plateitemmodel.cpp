#include "plateitemmodel.h"

PlateItemModel::PlateItemModel()
{

}

QVariant PlateItemModel::data(const QModelIndex &index, int role) const
{
    return "test";
}

int PlateItemModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int PlateItemModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QModelIndex PlateItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex PlateItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}
