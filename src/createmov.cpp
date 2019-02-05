#include "createmov.h"
#include <QImage>

CreateMov::CreateMov(QObject *parent) : QObject(parent)
{

}

void CreateMov::avinit()
{
    avformat_alloc_output_context2(&oc,nullptr,nullptr,outFile.absoluteFilePath().toLocal8Bit());
    codec = avcodec_find_encoder_by_name("prores");
    stream = avformat_new_stream(oc,codec);
    stream->id = static_cast<int>(oc->nb_streams-1);
    codectx = avcodec_alloc_context3(codec);

    codectx->bit_rate = 400000;
    codectx->profile = 1;
    codectx->width = width;
    codectx->height = height;

    stream->time_base = AVRational{1,24};
    codectx->time_base = stream->time_base;

    codectx->gop_size = 12;
    codectx->pix_fmt = AV_PIX_FMT_YUV422P10LE;

    if(oc->oformat->flags & AVFMT_GLOBALHEADER)
        codectx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    AVDictionary *opt = nullptr;

    avcodec_open2(codectx,codec,&opt);
    av_dict_free(&opt);
}

void CreateMov::setOutFile(QFileInfo fileInfo)
{
    outFile = fileInfo;
}

void CreateMov::setSize(int w,int h)
{
    width = w;
    height = h;
}

void CreateMov::setFrameRate(float rate)
{

}

void CreateMov::avFrameSetting()
{
    frame = av_frame_alloc();
    frame->format = codectx->pix_fmt;
    frame->width = width;
    frame->height = height;
    av_frame_get_buffer(frame,0);

    frame_tmp = av_frame_alloc();
    frame_tmp->format = AV_PIX_FMT_RGB24;
    frame_tmp->width = width;
    frame_tmp->height = height;
    av_frame_get_buffer(frame_tmp,0);

    avcodec_parameters_from_context(stream->codecpar,codectx);

    avio_open(&oc->pb,oc->filename,AVIO_FLAG_WRITE);

    avformat_write_header(oc,nullptr);


}

void CreateMov::getVideoFrame(QImage image,int num)
{
    int x,y;
    av_frame_make_writable(frame);
    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            frame_tmp->data[0][(y*width*3)+(x*3)+2] = image.bits()[(y*width*4)+(x*4)];
            frame_tmp->data[0][(y*width*3)+(x*3)+1] = image.bits()[(y*width*4)+(x*4)+1];
            frame_tmp->data[0][(y*width*3)+(x*3)] = image.bits()[(y*width*4)+(x*4)+2];
        }
    }
    sws_ctx = sws_getContext(width,height,AV_PIX_FMT_RGB24,width,height,AV_PIX_FMT_YUV422P10LE,SWS_BICUBIC,NULL,NULL,NULL);
    sws_scale(sws_ctx,(const uint8_t * const *)frame_tmp->data,frame_tmp->linesize,0,height,frame->data,frame->linesize);
    frame->pts = num;
    av_init_packet(&pkt);
    avcodec_encode_video2(codectx,&pkt,frame,&got_packet);

    if(got_packet)
    {
        av_packet_rescale_ts(&pkt,codectx->time_base,stream->time_base);
        pkt.stream_index = stream->index;
        av_write_frame(oc,&pkt);
        av_packet_unref(&pkt);
    }

}

void CreateMov::releaseMov()
{
    av_write_trailer(oc);
    avcodec_free_context(&codectx);
    av_frame_free(&frame);
    av_frame_free(&frame_tmp);
    sws_freeContext(sws_ctx);
    avio_closep(&oc->pb);
    avformat_free_context(oc);
}
