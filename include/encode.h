#ifndef ENCODE_H
#define ENCODE_H

// now include project files
#include "common.h"
#include "output.h"
#include "decode.h"

// now link up to the proper libraries needed 
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

// now initialize an encoding job structure
struct EncodingJob {
	
	// introduce high level elements
	char * inputPath;
	char * outputPath;
	char * outputFormat;

	// high level codec information
	int codecId;

	// initialize lower level video elements
	int videoBitrate;
	int height;
	int width;

	// initialize time base for creating frames per second elements
	// fps = 29970 / 1000 -- apple input elements
	struct time_base {
	
		int num;
		int den;
	} fps;

	// initialize gop_size - normally 12 for various elements etc
	int gop_size;

	// initialize / finetune audio elements 
	int audioBitrate;
	int sampleRate;	
};

// now lets declare a namspace structure to export this module under
typedef struct {

	// pass in an inputPath and an output path for the encoding of the video
	// in the future we will pass in a type of codec as well
	const char * (* const encodeVideo)(EncodingJob *);

} encode_namespace;

// now lets declare the structure variable so we can actually inject elements into it in the implementation
extern encode_namespace const encode;

#endif // ENCODE_H
