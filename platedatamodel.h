#ifndef PLATEDATAMODEL_H
#define PLATEDATAMODEL_H

#include <QAbstractItemModel>

class PlateDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    PlateDataModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const override;

};

#endif // PLATEDATAMODEL_H
