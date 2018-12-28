#ifndef DPXREADER_H
#define DPXREADER_H

#include <QImage>
#include <QString>
#include "DPXimage_Header.h"

class DpxReader
{
public:
    DpxReader();
    ~DpxReader();
    DpxReader(QString path);
    QSize getSize();
    QImage getQImage();
    bool isValid;

private:
    DPXHeader *dpxHeader;
    unsigned int *bits;
    bool isBigEndian;
    int width;
    int height;
    int offset;
};

#endif // DPXREADER_H
