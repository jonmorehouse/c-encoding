#include "encode.h"

// now include any  libraries needed for application
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

// now include erroneous, temp libraries here
#include <stdio.h>

// actually encode the video here calling private methods etc
static void encodeVideo(const char * inputPath, const char * outputPath, EncodingJob * encodingJob) {
	
	// initialize the codec struct for this element
	AVCodec * codec;
	
	// http://ffmpeg.org/doxygen/trunk/structAVCodecContext.html
	AVCodecContext * codecContext = NULL;
	
	// initialize a file pointer 
	FILE * file;

	// decoded raw or video data
	// http://ffmpeg.org/doxygen/trunk/structAVFrame.html
	AVFrame * frame;

	// store compressed data with packet type 
	AVPacket packet;

	// create the ending needed for this file
	uint8_t endcode = {0, 0, 1, 0xb7 };

	// lets link up and get the correct codec from the one passed in
	// if it doesn't exist, then lets print an error etc
	codec = avcodec_find_encoder(encodingJob->codecId);	

	// now lets make sure that a valid codec is being used
	if (!codec) return;

	// now lets make sure that we have the codec
	codecContext = avcodec_alloc_context3(codec);	

	// now lets return the codec context etc
	if (!codecContext) return;
	
	// now link up the various parameters passed into the job in our codec context etc
	codecContext->bit_rate = encodingJob->bitrate;
	codecContext->width = encodingJob->width;
	codecContext->height = encodingJob->height;
	
	// now link up the fps from the previous section etc
	codecContext->time_base = (AVRational){1,25};
	
	// now link up the gop_size	
	// emit one intra frame every ten frames
	// http://www.batchframe.com/quick-tips/tip.php?t=3
	codecContext->gop_size = 10;

	// 
	codecContext->max_b_frames = 1;
	codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
		
	// now lets create some hooks in case the codec we are outputting is h264
	if (encodingJob->codecId == AV_CODEC_ID_H264) {
	
		//  
		av_opt_set(codecContext->priv_data, "preset", "slow", 0);

	}

	// now open codec. Make sure we can successfully open it etc
	if (avcodec_open2(codecContext, codec, NULL) < 0) return;

	// now open the file

	
	

}

// now implement the namespace struct that was initialized as an external variable in previous header
encode_namespace const encode = {encodeVideo};


