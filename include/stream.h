#ifndef STREAM_H
#define STREAM_H

/*
 * Responsible for creating output streams as needed for transcoding
 *  
 *  1.) audio stream creation -- create an audio stream given a viable input context
 *  2.) video stream creation -- create a valid video stream given the correct input etc
 *
 *  Pending:
 *
 *  	-	write to stream -- does it make sense here?
 *  	-	close streams etc
 */
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

// declare a namespace structure for these elements
typedef struct {
	
	// create a video stream given the correct inputs needed
	AVStream * (* const createStream)(AVFormatContext * , AVCodec ** , enum AVCodecID);	


	//AVFormatContext * (* const getFormatContext)(const char *);

} stream_namespace;

// initialize a namespace holding variable
extern stream_namespace const stream;

#endif // STREAM_H
