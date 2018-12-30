#include "dpxreader.h"
#include <fstream>
#include <string>

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
        QImage image(getSize(),QImage::Format_RGB32);
        unsigned char *buff = image.bits();
        for(int i = 0; i < width*height; i++)
        {
            /*
             * QImage의 Fromat_RGB32에서 0xFF000000 자리에 FF값이 Alpha 처럼 작동한다. 추가 해주지않으면 흰색으로 나옴
             */
            bits[i] = ((bits[i]&0x00000FFC)>>4)|((bits[i]&0x003FC000)>>6)|((bits[i]&0xFF000000)>>8)|(0xFF000000);
        }
        memcpy(buff,bits,width*height*4);

        return image;
    }else{
        return QImage();
    }
}
