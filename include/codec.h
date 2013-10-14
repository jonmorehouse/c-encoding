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
#include <libavutil/channel_layout.h>

typedef struct {

	int (* const selectChannelLayout)(AVCodec * Codec);

	// create individual codecs for each video stream
	void (* const createAudioCodec)(Output *, EncodingJob *);
	void (* const createVideoCodec)(Output *, EncodingJob *);

	// open and initialize codecs based upon input streams
	void (* const openCodec)(Output *, enum AVMediaType);

} codec_namespace;

// initialize the output codec etc
extern codec_namespace const codec;

#endif //codec_h
