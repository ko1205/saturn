#ifndef EXRREADER_H
#define EXRREADER_H

#include <QImage>
#include <QString>
#include <ImfRgbaFile.h>
#include <ImfArray.h>
//#include "DPXimage_Header.h"

class ExrReader
{
public:
    ExrReader();
    ~ExrReader();
    ExrReader(QString path);
    QSize getSize();
    QImage getQImage();
    bool isValid;

private:
//    unsigned int *bits;
    Imf::Array<Imf::Rgba> pixels;

//    bool isBigEndian;
    int width;
    int height;
//    int offset;
};

#endif // DPXREADER_H
