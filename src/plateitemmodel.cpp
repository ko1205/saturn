#include "plateitemmodel.h"
#include <QPixmap>

PlateItemModel::PlateItemModel(QObject *parent)
    : QAbstractItemModel(parent)
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
            /*
             * 아래 scaled함수는 정리후 Delegate class로 이동 예정
             */
//            return item.thumbnail.scaled(300,100,Qt::KeepAspectRatio);
            return item.thumbnail;
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
    case 2:
        if(role == Qt::DisplayRole)
        {
//            if(!item.singleFrame){
//                 return QString::number(item.frame.first) + "~" + QString::number(item.frame.second);
//            }else {
//                return "Single Frame";
//            }
            return QVariant::fromValue(item.frame);
        }else{
            return QVariant();
        }
    case 3:
        if(role == Qt::DisplayRole)
        {
            return QDir::toNativeSeparators(item.path.absolutePath());
        }else{
            return QVariant();
        }
    case 4:
        /*
         * 수정이 필요한곳에는 data() 함수의 Qt::EditRole 도 지정을 해주어야 delegate의 edit에서 값을 받을수 있다
         */
        if(role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return item.secne;
        }else{
            return QVariant();
        }
    case 5:
        if(role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return item.shot;
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
    return 7;
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
            return "Source Path";

        case 4:
            return "Scene";

        case 5:
            return "Shot";

        case 6:
            return "ColorSpace";

        default:
            return section+1;
        }

    }else{
        return section+1;
    }
}

Qt::ItemFlags PlateItemModel::flags(const QModelIndex &index) const
{
    if(index.column() == 4 || index.column() == 5)
    {
        return Qt::ItemIsSelectable
                |Qt::ItemIsEnabled
                |Qt::ItemIsEditable;
    }else{
        return Qt::ItemIsSelectable
                |Qt::ItemIsEnabled;
    }
}

bool PlateItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column() == 4)
    {
        items[index.row()].secne = value.toString();
        emit dataChanged(index, index, {role});
        return true;
   }else if(index.column() == 5){
        items[index.row()].shot = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

void PlateItemModel::appendRow(PlateItem item)
{
    beginInsertRows(QModelIndex(),0,0);
    items.append(item);
    endInsertRows();
}

void PlateItemModel::clear()
{
    beginResetModel();
    items.clear();
    endResetModel();
}

PlateItem::PlateItem()
{
    thumbnail.load("/Users/ghchoi/storage/Data/test_images/A193_C003_0704V4_289/JPEG/A193_C003_0704V4.0000289.jpg");
    fileName = "A195_C003_0704C9.0000252.jpg";
    path.setCurrent("/Users/ghchoi/storage/Data/test_images/A193_C003_0704V4_289/JPEG/");
    frame = QPair<long long,long long>(10,256);
    colorSpace = "log";

}
