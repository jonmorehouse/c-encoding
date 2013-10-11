#ifndef CODEC_H
#define CODEC_H

/*
 * Initialize output codecs etc
 *
 *
*/
#include "common.h"
#include "encode.h"
#include "output.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

typedef struct {

	AVCodec * (* const createAudioCodec)(Output *, EncodingJob *);
	AVCodec * (* const createVideoCodec)(Output *, EncodingJob *);

} codec_namespace;

// initialize the output codec etc
extern codec_namespace const codec;

#endif // codec_h
