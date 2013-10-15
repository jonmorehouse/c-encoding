#ifndef DECODE_H
#define DECODE_H

// include project dependencies
#include "common.h"

// include proper ffmpeg related libraries
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>


// initialize the type structure
struct Input {

	AVFormatContext * context;
	AVFrame * frame;
	AVCodec * audioCodec;
	AVCodec * videoCodec;
	AVCodecContext * audioCodecContext;
	AVCodecContext * videoCodecContext;
	AVPacket * packet;

}; 

// declare a structure to export all of the functions that we are declaring in this namespace etc
typedef struct {

	// create an element to get the formatContext from the input filePath
	AVFormatContext * (* const getFormatContext)(const char *);

	// create a simple decode element
	// in the future, this should take in callback function so that we can pass the individual frame into each one
	void (* const fromPath)(const char *);

	// now initialize decode video / audio functions
	void (* const decodeAudio)(Input *);

	// decode video into the input element properly
	void (* const decodeVideo)(Input *);

	// now init an input method
	// responsible for creating a full input with everything needed
	Input * (* const InputInit)(const char *);

} decode_namespace;

// declare a structure variable that can be accessed from exterior calling functions
extern  decode_namespace const decode;

#endif // DECODE_H
