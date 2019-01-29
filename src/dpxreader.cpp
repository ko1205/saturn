#include "dpxreader.h"
#include <fstream>
#include <string>
#include <math.h>

DpxReader::DpxReader()
{
    isValid = false;
}

DpxReader::DpxReader(QString path)
{
    dpxHeader = new DpxHeader();
    std::ifstream iFile;
    iFile.open(path.toLocal8Bit(),std::ios::binary|std::ios::in);
    iFile.read((char*)dpxHeader,sizeof(DPXHeader));
    if(dpxHeader->file.magic_num == DPX_MAGIC)
    {
        isBigEndian = false;
    }else if(dpxHeader->file.magic_num == DPX_MAGIC_FLIPPED){
        isBigEndian = true;
    }else{
        isValid = false;
        return;
    }

    isValid = true;
    if(isBigEndian)
    {
        dpxHeader->file.offset = Endian32_Swap(dpxHeader->file.offset);
        dpxHeader->image.pixels_per_line = Endian32_Swap(dpxHeader->image.pixels_per_line);
        dpxHeader->image.lines_per_image_ele = Endian32_Swap(dpxHeader->image.lines_per_image_ele);
    }
    width = dpxHeader->image.pixels_per_line;
    height = dpxHeader->image.lines_per_image_ele;
    offset = dpxHeader->file.offset;
    bits = new unsigned int[width*height];
    iFile.seekg(offset);

    iFile.read((char*)bits,width*height*4);
    if(isBigEndian)
    {
        for(int i=0;i<width*height;i++)
        {
            bits[i] = Endian32_Swap(bits[i]);
        }
    }

    iFile.close();
}

DpxReader::~DpxReader()
{
    if(bits!=NULL)
    {
        delete [] bits;
    }
    delete dpxHeader;

}

QSize DpxReader::getSize()
{
    if(isValid)
    {
        return QSize(width,height);
    }else{
        return QSize();
    }
}

QImage DpxReader::getQImage()
{
    if(isValid)
    {
        int j = 0;
        QImage image(getSize(),QImage::Format_RGB32);
        unsigned char *buff = image.bits();
        nukeLutMake();
        for(int i = 0; i < width*height; i++)
        {
            /*
             * QImage의 Fromat_RGB32에서 0xFF000000 자리에 FF값이 Alpha 처럼 작동한다. 추가 해주지않으면 흰색으로 나옴
             */
//            bits[i] = ((bits[i]&0x00000FFC)>>4)|((bits[i]&0x003FC000)>>6)|((bits[i]&0xFFC00000)>>8)|(0xFF000000);
            buff[j+0] = lut[((bits[i]&0x00000FFC)>>2)];
            buff[j+1] = lut[((bits[i]&0x003FF000)>>12)];
            buff[j+2] = lut[((bits[i]&0xFFC00000)>>22)];
            buff[j+3] = 255;
            j=j+4;

        }
//        memcpy(buff,bits,width*height*4);

        return image;
    }else{
        return QImage();
    }
}

void DpxReader::nukeLutMake()
{
    for(int i = 0; i < 1024; i++)
    {
        float temp = ((pow(10,((float)i-685)/300)-0.0108)/(1-0.0108));
        temp = temp<0.003131 ? (temp*12.92) : ((pow(temp,1/2.4))*1.055)-0.055;
        temp = temp < 1 ? (temp < 0 ? 0 : temp) : 1;
        lut[i] = (unsigned)(temp*255);
    }
}
