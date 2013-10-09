#ifndef CODEC_H
#define CODEC_H

/*
 * Initialize output codecs etc
 *
 *
*/
#include "encode.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

typedef struct {

	AVCodec * (* const createAudioCodec)(AVFormatContext *, EncodingJob *);
	AVCodec * (* const createVideoCodec)(AVFormatContext *, EncodingJob *);

} codec_namespace;

// initialize the output codec etc
extern codec_namespace const codec;

#endif // codec_h
