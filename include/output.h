#ifndef OUTPUT_H
#define OUTPUT_H

// now include the encode header
#include "common.h"
#include "codec.h"
#include "encode.h"
#include "bitstream_filter.h"
#include "write.h"
#include "decode.h"

// now link up to the proper libraries needed 
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
//#include <libswscale/swscale_internal.h>
#include <libavutil/imgutils.h>

// encapsulate all of the information needed to output to a format etc
struct Output{
	
	// initialize the context for output
	AVFormatContext * context;
	AVOutputFormat * format;

	// initialize both codecs for this element
	AVCodec * audioCodec;
	AVCodec * videoCodec;

	// initialize contexts for each of the output streams
	AVCodecContext * audioCodecContext;
	AVCodecContext * videoCodecContext;

	// initialize the streams for output 
	AVStream * audioStream;
	AVStream * videoStream;

	// initialize bitstream filter context 
	// filter contexts etc
	AVBitStreamFilterContext * bitStreamFilterContext;
	struct SwsContext * resizeContext;

	// initialize output packet and frame for actual creation fo the output streams and frames etc
	AVFrame * frame;
	AVPacket * packet;
};

// declare a structure type that is responsible for holding all the elements needed
typedef struct {

	// creating output elements
	AVFormatContext * (* const createFormatContext)(const char *, const char *);

	// create a valid output from an encoding job input etc
	Output * (* const OutputInit)(const EncodingJob *, const Input *);

	// writing to output elements
	void (* const writeVideoFrame)(AVPacket *, Output *);
	void (* const  writeAudioFrame)(AVPacket *, Output *);
	void (* const packetHandler)(Input *, Output *)

} output_namespace;

// 
extern output_namespace const output;

#endif //output_h

