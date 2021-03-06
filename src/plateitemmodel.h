#ifndef PLATEITEMMODEL_H
#define PLATEITEMMODEL_H

#include <QAbstractItemModel>
#include <QDir>
#include <QImage>

class PlateItem
{
public:
    PlateItem();
    QImage thumbnail;
    QString fileName;
    QDir path;
    QPair<long long,long long> frame;
    QString secne;
    QString shot;
    QString colorSpace;
    QString firstFileName;
    bool singleFrame;
    QString subName;
    int pendingCount;

};

class PlateItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    PlateItemModel(QObject *parent = Q_NULLPTR);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void appendRow(PlateItem item);
    PlateItem *getItem(int row);

public slots:
    void clear();

private:
    QList<PlateItem> items;

};

#endif // PLATEITEMMODEL_H
