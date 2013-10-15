#include "decode.h"

// include project dependencies
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

// include temp development dependencies
#include <stdio.h>

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

// responsible for taking the decoded packet and placing it into the raw data buffer for easy encoding and output
static void decodeVideo(Input * input) {

	// the packet should be of a different size	



}

static void decodeAudio(Input * input) {




}

Input * InputInit(const char * inputPath) {

	int iterator = 0;

	// allocate space for an input
	Input * input = malloc(sizeof(Input));	
	
	// initialize the various pieces needed for allocation
	input->context = getFormatContext(inputPath);

	// now initialize the audio codecss
	for (iterator = 0; iterator < input->context->nb_streams; iterator++) {
	
		// discover what type of stream this is
		if (input->context->streams[iterator]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			
			// now initialize the stream elements
			input->audioStream = input->context->streams[iterator];
			input->audioCodecContext = input->audioStream->codec;

			// now allocate the correct audio codec
			input->audioCodec = avcodec_find_decoder(input->audioCodecContext->codec_id);

			// now lets ensure that we grabbed the correct input audioCodec
			if (!input->audioCodec) ;// handle errors here with elegance
		}

		// initialize the video stream information as needed
		else if (input->context->streams[iterator]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {

			input->videoStream = input->context->streams[iterator];
			input->videoCodecContext = input->videoStream->codec;

			// now allocate teh correct video codec for this element
			input->videoCodec = avcodec_find_decoder(input->videoCodecContext->codec_id);

			// now ensure that the video codec is there
			if (!input->videoCodec) ;//

		}
	}

	// allocate a frame and a raw data buffer
	input->frame = avcodec_alloc_frame();

	// now lets get the number of bytes needed for this application
	input->bufferSize= avpicture_get_size(input->videoCodecContext->pix_fmt, input->videoCodecContext->width, input->videoCodecContext->height);

	// now lets get the correct sample size
	// now lets initialize this area in memory
	input->buffer = (uint8_t *)malloc(input->bufferSize * sizeof(uint8_t));
		
	return input;
}

// initialize our constant decode struct for exporting etc
decode_namespace const decode = {
	
	// helper methods for use with application
	// create an input context for the video
	.getFormatContext = getFormatContext, 

	.decodeAudio = decodeAudio,
	.decodeVideo = decodeVideo,

	.InputInit = InputInit,


};

