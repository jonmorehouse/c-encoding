#ifndef BITSTREAM_FILTER_H
#define BITSTREAM_FILTER_H

// now include the correct project headers
#include "common.h"
#include "output.h"
#include "encode.h"

// now require the proper libav* libraries that are needed
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

// 
typedef struct {

	// initialize the bitstream filters 
	void (* const initBitstreamFilters)(Output *);	

	// filter the video using the packet
	void (* const filter)(AVPacket *, Output *);

} bitstream_filter_namespace;

// now lets declare an output namespace structure instance 
extern bitstream_filter_namespace const bitstream_filter;

#endif // BITSTREAM_fILTER_H
