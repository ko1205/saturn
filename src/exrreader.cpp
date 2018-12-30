#include "exrreader.h"
#include <fstream>
#include <string>

ExrReader::ExrReader()
{
    isValid = false;
}

ExrReader::ExrReader(QString path)
{
    Imf::RgbaInputFile inFile(path.toLocal8Bit());
    Imath::Box2i dw = inFile.dataWindow();
    width = dw.max.x - dw.min.x+1;
    height = dw.max.y - dw.min.y+1;
    pixels.resizeErase(width*height);
    inFile.setFrameBuffer(&pixels[0] - dw.min.x - dw.min.y * width,1,width);
    inFile.readPixels(dw.min.y,dw.max.y);
    isValid = true;

//    dpxHeader = new DpxHeader();
//    std::ifstream iFile;
//    iFile.open(path.toLocal8Bit(),std::ios::binary|std::ios::in);
//    iFile.read((char*)dpxHeader,sizeof(DPXHeader));
//    if(dpxHeader->file.magic_num == DPX_MAGIC)
//    {
//        isBigEndian = false;
//    }else if(dpxHeader->file.magic_num == DPX_MAGIC_FLIPPED){
//        isBigEndian = true;
//    }else{
//        isValid = false;
//        return;
//    }

//    isValid = true;
//    if(isBigEndian)
//    {
//        dpxHeader->file.offset = Endian32_Swap(dpxHeader->file.offset);
//        dpxHeader->image.pixels_per_line = Endian32_Swap(dpxHeader->image.pixels_per_line);
//        dpxHeader->image.lines_per_image_ele = Endian32_Swap(dpxHeader->image.lines_per_image_ele);
//    }
//    width = dpxHeader->image.pixels_per_line;
//    height = dpxHeader->image.lines_per_image_ele;
//    offset = dpxHeader->file.offset;
//    bits = new unsigned int[width*height];
//    iFile.seekg(offset);

//    iFile.read((char*)bits,width*height*4);
//    if(isBigEndian)
//    {
//        for(int i=0;i<width*height;i++)
//        {
//            bits[i] = Endian32_Swap(bits[i]);
//        }
//    }

//    iFile.close();
}

ExrReader::~ExrReader()
{
//    if(data!=NULL)
    {
//        delete [] data;
    }
}

QSize ExrReader::getSize()
{
    if(isValid)
    {
        return QSize(width,height);
    }else{
        return QSize();
    }
}

QImage ExrReader::getQImage()
{
    if(isValid)
    {
        QImage image(getSize(),QImage::Format_RGB32);
        unsigned char *buff = image.bits();
        for(int n = 0; n < height ; n++ ){
            int j = n*width;
            for( int m = 0; m < width; m++ ){
                int i = j+m;

                float r = (pixels[i].r);
                float g = (pixels[i].g);
                float b = (pixels[i].b);

                r = r >1 ? 1 : r < 0 ? 0 : r;
                g = g >1 ? 1 : g < 0 ? 0 : g;
                b = b >1 ? 1 : b < 0 ? 0 : b;

                buff[(j*4)+(m*4)] = ((Imath::Math<float>::pow(b,0.4545))*255);
                buff[(j*4)+(m*4)+1] = ((Imath::Math<float>::pow(g,0.4545))*255);
                buff[(j*4)+(m*4)+2] = ((Imath::Math<float>::pow(r,0.4545))*255);
                buff[(j*4)+(m*4)+3] = 255;

            }
        }



//        for(int i = 0; i < width*height; i++)
//        {
//            /*
//             * QImage의 Fromat_RGB32에서 0xFF000000 자리에 FF값이 Alpha 처럼 작동한다. 추가 해주지않으면 흰색으로 나옴
//             */
//            bits[i] = ((bits[i]&0x00000FFC)>>4)|((bits[i]&0x003FC000)>>6)|((bits[i]&0xFF000000)>>8)|(0xFF000000);
//        }
//        memcpy(buff,bits,width*height*4);

        return image;
    }else{
        return QImage();
    }
}
