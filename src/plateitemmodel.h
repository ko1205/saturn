#ifndef PLATEITEMMODEL_H
#define PLATEITEMMODEL_H

#include <QAbstractItemModel>


class PlateItemModel : public QAbstractItemModel
{
public:
    PlateItemModel();
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // PLATEITEMMODEL_H
