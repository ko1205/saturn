#ifndef ITEM_H
#define ITEM_H

//#include<QtCore>
#include<QtWidgets>

class item
{
public:
    item();
    ~item();
    static int count;

private:
    QImage thumnail;
    QString path;
    QString fileName;
    QPair<int,int> frameRange;
    QString targetName;
    QString colorspace;
    double frameRate;
    bool selected;
    QString scene;
    QString shot;
};

#endif // ITEM_H
