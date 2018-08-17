#include "platedatamodel.h"

PlateDataModel::PlateDataModel(QObject *parent)
    :QAbstractItemModel(parent)
{

}

QVariant PlateDataModel::data(const QModelIndex &index, int role) const
{
    return QString("test");
}

QModelIndex PlateDataModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
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
