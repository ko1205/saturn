#ifndef CREATEMOV_H
#define CREATEMOV_H

#include <QObject>
extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/timestamp.h>
}

class CreateMov : public QObject
{
    Q_OBJECT
public:
    explicit CreateMov(QObject *parent = 0);
    void avinit();

signals:

public slots:

private:
    AVFormatContext *oc;
    AVCodec *codec;
    AVStream *stream;
    AVCodecContext *codectx;
    AVFrame *frame;
    int got_packet = 0;
    AVPacket pkt = {0};
};

#endif // CREATEMOV_H
