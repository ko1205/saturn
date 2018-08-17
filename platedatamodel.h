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


};

#endif // PLATEDATAMODEL_H
