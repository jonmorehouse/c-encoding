#ifndef ENCODE_H
#define ENCODE_H

// now link up to the proper libraries needed etc
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// now lets declare a namspace structure to export this module under
typedef struct {

	// pass in an inputPath and an output path for the encoding of the video
	// in the future we will pass in a type of codec as well
	void (* const encodeVideo)(const char *, const char *);

} namespace_struct;

// now lets declare the structure variable so we can actually inject elements into it in the implementation
extern namespace_struct const encode;

#endif // ENCODE_H
