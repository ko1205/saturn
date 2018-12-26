#include "plateitemmodel.h"
#include <QPixmap>

PlateItemModel::PlateItemModel()
{
//    for(int i = 0;i < 30; i++)
//    {
//        PlateItem item;
//        items.append(item);
//    }

}

QVariant PlateItemModel::data(const QModelIndex &index, int role) const
{
//    if(role == Qt::DecorationRole)
//    {
//        return QPixmap("/Users/ghchoi/storage/Data/test_images/A193_C003_0704V4_289/JPEG/A193_C003_0704V4.0000289.jpg");
//    }else{
//        return QVariant();
//    }
    PlateItem item = items.at(index.row());
    switch (index.column()) {
    case 0:
        if(role == Qt::DecorationRole)
        {
            return item.thumbnail.scaled(100,100,Qt::KeepAspectRatio);
        }else{
            return QVariant();
        }
    case 1:
        if(role == Qt::DisplayRole)
        {
            return item.fileName;
        }else{
            return QVariant();
        }
    default:
        return QVariant();
    }
}

int PlateItemModel::rowCount(const QModelIndex &parent) const
{
    return items.count();
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

void PlateItemModel::appendRow(PlateItem item)
{
    beginInsertRows(QModelIndex(),0,0);
    items.append(item);
    endInsertRows();
}

PlateItem::PlateItem()
{
    thumbnail.load("/Users/ghchoi/storage/Data/test_images/A193_C003_0704V4_289/JPEG/A193_C003_0704V4.0000289.jpg");
    fileName = "A195_C003_0704C9.0000252.jpg";
    path.setCurrent("/Users/ghchoi/storage/Data/test_images/A193_C003_0704V4_289/JPEG/");
    frame = QPair<long long,long long>(10,256);
    colorSpace = "log";

}
