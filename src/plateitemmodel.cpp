#include "plateitemmodel.h"

PlateItemModel::PlateItemModel()
{

}

QVariant PlateItemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        return "test";
    }else{
        return QVariant();
    }
}

int PlateItemModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int PlateItemModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QModelIndex PlateItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex PlateItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant PlateItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return "Thumbnail";

        case 1:
            return "File Name";

        case 2:
            return "Frame Range";

        case 3:
            return "Scene";

        case 4:
            return "Shot";

        case 5:
            return "ColorSpace";

        default:
            return section+1;
        }

    }else{
        return section+1;
    }
}
