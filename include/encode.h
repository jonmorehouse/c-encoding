#ifndef ENCODE_H
#define ENCODE_H

// now include project files
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
typedef struct {
	
	int codecId;
	int bitrate;
	int height;
	int width;
	float fps;
	char * inputPath;
	char * outputPath;
	char * outputFormat;

} EncodingJob;

// now lets declare a namspace structure to export this module under
typedef struct {

	// create the input format context etc
	AVFormatContext * (* const createFormatContext)(const char *, const char *);

	// initialize the codec for encoding output
	void (* const initializeCodec)(AVCodec **, AVStream **, const AVFormatContext *, const EncodingJob *);	

	// pass in an inputPath and an output path for the encoding of the video
	// in the future we will pass in a type of codec as well
	const char * (* const encodeVideo)(EncodingJob *);

} encode_namespace;

// now lets declare the structure variable so we can actually inject elements into it in the implementation
extern encode_namespace const encode;

#endif // ENCODE_H
