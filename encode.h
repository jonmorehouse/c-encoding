#ifndef ENCODE_H
#define ENCODE_H

// now include project files
#include "decode.h"

// now link up to the proper libraries needed 
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// now initialize an encoding job structure
typedef struct {
	
	int codecId;
	int bitrate;
	int height;
	int width;
	float fps;

} EncodingJob;

// now lets declare a namspace structure to export this module under
typedef struct {

	// create the input format context etc
	AVFormatContext * (* const createFormatContext)(const char *);

	// pass in an inputPath and an output path for the encoding of the video
	// in the future we will pass in a type of codec as well
	void (* const encodeVideo)(const char *, const char *, EncodingJob *);

} encode_namespace;

// now lets declare the structure variable so we can actually inject elements into it in the implementation
extern encode_namespace const encode;

#endif // ENCODE_H
