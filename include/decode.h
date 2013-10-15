#ifndef DECODE_H
#define DECODE_H

// include project dependencies
#include "common.h"

// include proper ffmpeg related libraries
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// initialize the type structure
struct Input {

	// initialize general elements
	AVFormatContext * context;
	AVFrame * frame;
	AVPacket * packet;

	// number of bytes we are permitting for this application
	// this is guessed based upon the size of the input picture
	int bufferSize;

	// whether or not we got a frame
	int gotFrame;

	// now create a place to store this input buffered data
	// this should be rotated between audio/video for best performance
	uint8_t * buffer;

	// initialize audio elements
	AVCodec * audioCodec;
	AVStream * audioStream;
	AVCodecContext * audioCodecContext;

	// initialize video elements
	AVCodec * videoCodec;
	AVStream * videoStream;
	AVCodecContext * videoCodecContext;
}; 

// declare a structure to export all of the functions that we are declaring in this namespace etc
typedef struct {

	// create an element to get the formatContext from the input filePath
	AVFormatContext * (* const getFormatContext)(const char *);

	// now initialize decode video / audio functions
	void (* const decodeAudio)(Input *);

	// decode video into the input element properly
	void (* const decodeVideo)(Input *);

	// now init an input method
	// responsible for creating a full input with everything needed
	Input * (* const InputInit)(const char *);

	// close out input as needed
	void (* const InputClose)(Input *);

} decode_namespace;

// declare a structure variable that can be accessed from exterior calling functions
extern  decode_namespace const decode;

#endif // DECODE_H
