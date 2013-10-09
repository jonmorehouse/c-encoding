#ifndef OUTPUT_H
#define OUTPUT_H

// now link up to the proper libraries needed 
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

// declare a structure type that is responsible for holding all the elements needed
typedef struct {

	void (* const writeVideoFrame)(AVPacket *, AVFormatContext *);
	void (* const  writeAudioFrame)(AVPacket *, AVFormatContext *);
	void (* const packetHandler)(AVPacket *, AVFormatContext *);

} output_namespace;

//
extern output_namespace const output;


#endif //output_h

