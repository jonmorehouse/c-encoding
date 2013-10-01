#ifndef DECODE_H
#define DECODE_H

// include proper ffmpeg related libraries
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// declare a structure to export all of the functions that we are declaring in this namespace etc
typedef struct {

	// create an element to get the formatContext from the input filePath
	AVFormatContext * (* const getFormatContext)(const char *);
	int (* const getVideoStreamIndex)(const AVFormatContext *);

	// create a simple decode element
	// in the future, this should take in callback function so that we can pass the individual frame into each one
	void (* const fromPath)(const char *);

} decode_namespace;

// declare a structure variable that can be accessed from exterior calling functions
extern  decode_namespace const decode;

#endif // DECODE_H
