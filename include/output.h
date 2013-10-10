#ifndef OUTPUT_H
#define OUTPUT_H

// now include the encode header
#include "common.h"
#include "encode.h"

// now link up to the proper libraries needed 
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

// encapsulate all of the information needed to output to a format etc
struct Output{
	
	AVFormatContext * context;
	AVCodec * audioCodec;
	AVCodec * videoCodec;
	AVStream * audioStream;
	AVStream * videoStream;
	int test;
};

// declare a structure type that is responsible for holding all the elements needed
typedef struct {

	// creating output elements
	AVFormatContext * (* const createFormatContext)(const char *, const char *);

	// create a valid output from an encoding job input etc
	Output * (* const OutputInit)(EncodingJob *);

	// writing to output elements
	void (* const writeVideoFrame)(AVPacket *, AVFormatContext *);
	void (* const  writeAudioFrame)(AVPacket *, AVFormatContext *);
	void (* const packetHandler)(AVPacket *, AVFormatContext *);

} output_namespace;

// 
extern output_namespace const output;

#endif //output_h

