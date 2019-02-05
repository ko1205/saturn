#ifndef CREATEMOV_H
#define CREATEMOV_H

#include <QObject>
#include <QFileInfo>

extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
#include <libswscale/swscale.h>
}

class CreateMov : public QObject
{
    Q_OBJECT
public:
    CreateMov(QObject *parent = 0);
    void avinit();
    void setOutFile(QFileInfo fileInfo);
    void setSize(int w, int h);
    void setFrameRate(float rate);
    void avFrameSetting();
    void getVideoFrame(QImage image,int num);
    void releaseMov();
signals:

public slots:

private:
    AVFormatContext *oc;
    AVCodec *codec;
    AVStream *stream;
    AVCodecContext *codectx;
    AVFrame *frame;
    AVFrame *frame_tmp;
    int got_packet = 0;
    AVPacket pkt = {0};
    struct SwsContext *sws_ctx;

    QFileInfo outFile;
    int width;
    int height;
};

#endif // CREATEMOV_H
