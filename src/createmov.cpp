#include "createmov.h"

CreateMov::CreateMov(QObject *parent) : QObject(parent)
{
    avinit();
}

void CreateMov::avinit()
{
    avformat_alloc_output_context2(&oc,nullptr,nullptr,"test.mov");
    codec = avcodec_find_encoder_by_name("prores");
    stream = avformat_new_stream(oc,codec);
    stream->id = static_cast<int>(oc->nb_streams-1);
    codectx = avcodec_alloc_context3(codec);
}
