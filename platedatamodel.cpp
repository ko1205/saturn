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
