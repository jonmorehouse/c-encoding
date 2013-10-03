#include "decode.h"

// include project dependencies
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

// include temp development dependencies
#include <stdio.h>

// initialize the function that we are creating
// static global variable or function is seen only in the file its declared in
// http://stackoverflow.com/questions/572547/what-does-static-mean-in-a-c-program
static void fromPath(const char * filePath) {
	
	// allocate memory / pointers etc
	// allocate individual frame structure - note that mov / mpeg4 requires individual frames to be handled together etc
	// avframe describes decoded / raw audio / video data
	// http://ffmpeg.org/doxygen/trunk/structAVFrame.html
	AVFrame * frame; 
	
	// initialize a format context pointer
	AVFormatContext * formatContext = NULL;

	// initialize stream for reading from file buffer
	AVStream * stream;

	// now initialize codec context for storing information about codec etc
	AVCodecContext * codecContext;

	// initialize a codec
	AVCodec * codec;	

	// initialize packet storage container etc
	AVPacket packet;

	// initialize integers
	int counter = 0, videoStream = -1;

	// register all codecs available on the system
	av_register_all();

	// now lets open the file using av_open_input
	// pass in the format context pointer from above 
	// avformat_open_input(formatContext, filePath, bufferSize, formatOptions)
	// pass in NULL for last two to let avformat take care of everything under the hood (autodetect)
	if (avformat_open_input(&formatContext, filePath, NULL, NULL) != 0) {printf("ERROR");}
	
	// now lets get stream information
	// send a weird error handler if this is messed up etc
	if (avformat_find_stream_info(formatContext, NULL) < 0) { return -1; }

	// now format_context->nb_streams should be 2 (1 audio and video)
	// we just need to run through and grab the stream buffer from format_context->streams[i]
	int i;// initialize a counter etc
	
	// now lets loop through the streams and find the video stream
	for (i = 0; i < formatContext->nb_streams; i++) {
		
		// now lets grab the correct stream 
		if (formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
		
			videoStream = i;
			// break the for loop
			break;
		}
	}
	
	// now lets grab the actual codec needed for this stream etc
	codecContext = formatContext->streams[videoStream]->codec;

	// find the decoder for the stream
	codec = avcodec_find_decoder(codecContext->codec_id);
	
	// now lets make sure that the codec exists and throw an error or something etc
	if (codec == NULL) { printf("INVALID CODEC");}
	
	// now lets open the codec within our codecContext
	// note that the original function has been deprecated
	if (avcodec_open2(codecContext, codec, NULL) < 0) { printf("COULD NOT OPEN CODEC");}

	//create an avframe and set it to defaults
	//avframe describes decoded / raw audio/video data
	frame = avcodec_alloc_frame();
	
	// error handler here etc ... 
	if (!frame) { return 1; }

	// now lets get the required buffer size and allocate a buffer to hold the stream
	int numBytes = avpicture_get_size(PIX_FMT_RGB24, codecContext->width, codecContext->height);

	// uint8_t now create a place to store the bytewise data
	uint8_t * buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

	// allocate the correct number of bytes etc
}

// initialize getFormatContext element
static AVFormatContext * getFormatContext(const char * inputPath) {
	
	// need to open the file 				
	AVFormatContext * context = NULL;

	// now lets open the information and handle the errors properly etc
	if (avformat_open_input(&context, inputPath, NULL, NULL) < 0) {
		
		// handle errors elegantly here!

	}

	// now lets make sure that there are actually streams in this context
	if (avformat_find_stream_info(context, NULL) < 0) {

		// handle errors elegantly here
		// there are no media streams attached to this element
	}

	return context;
}


//  
static int getVideoStreamIndex(const AVFormatContext * context) {
	
	// now we are going to loop through each of the various streams and return an index to the video stream
	int index = -1;	
	unsigned int i = 0;

	// now loop through each of the streams and lets return the index!
	for (i < 0; i < context->nb_streams; i++) {

		// now do a long check to ensure that we are actually grabbing a valid video stream
		if (context->streams[i] && context->streams[i]->codec && context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {

			// reset the index to the correct value
			index = i;
			break;
		}
	}

	return index;
}



// initialize our constant decode struct for exporting etc
decode_namespace const decode = {.fromPath = fromPath, .getFormatContext = getFormatContext, .getVideoStreamIndex = getVideoStreamIndex, };

