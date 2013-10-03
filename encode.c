#include "utilities.h"
#include "encode.h"

// now include any  libraries needed for application
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

// now include erroneous, temp libraries here
#include <stdio.h>

/*
 * Initialize the output codec and stream accordingly
 * Open the codec for use, but don't open the stream
 */
static void initializeCodec(AVCodec ** inputCodec, AVStream ** inputStream, const AVFormatContext * context, const EncodingJob * job) {

	AVCodec * codec = *inputCodec;
	AVStream * stream = *inputStream;

	// now initialize the codec and stream elements as needed
	codec = avcodec_find_encoder(AV_CODEC_ID_H264);	

	// now initialize element	
	stream = avformat_new_stream(context, codec);

	// now handle errors as needed 
	if (!codec) ;// handle bad codec errors

	// now handle the bad stream output
	if (!stream) ;//

	// set defaults for the codec from the output context
	avcodec_get_context_defaults3(stream->codec, codec);

	// construct the encoder with the correct flags etc
	if (context->oformat->flags & AVFMT_GLOBALHEADER) 
		stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

	// initialize codec settings based upon input job		
	stream->codec->coder_type = AVMEDIA_TYPE_VIDEO;	
	stream->codec->pix_fmt = AV_PIX_FMT_YUV420P;
	stream->codec->width = job->width;
	stream->codec->height = job->height;
	stream->codec->codec_id = codec->id;
	stream->codec->bit_rate = job->bitrate;
	
	stream->codec->time_base.den = 25;
	stream->codec->time_base.num = 1;
	stream->codec->keyint_min = 25;
	stream->codec->max_b_frames = 3;
	stream->codec->b_frame_strategy = 1;
	stream->codec->scenechange_threshold = 40;
	stream->codec->refs = 6;
	stream->codec->qmin = 0;
	stream->codec->qmax = 0;
	stream->codec->qcompress = 0.6;
	stream->codec->max_qdiff = 4;
	stream->codec->i_quant_factor = 1.4;

	stream->codec->refs = 1;
	stream->codec->chromaoffset = -2;
	stream->codec->thread_count = 1;
	stream->codec->trellis = 1;
	stream->codec->me_range = 16;
	stream->codec->me_method = ME_HEX;
	stream->codec->flags2 |= CODEC_FLAG2_FAST;
	stream->codec->coder_type = 1;

	// initialize flags for h264 codec outputs
	if (stream->codec->codec_id == AV_CODEC_ID_H264)
		av_opt_set(stream->codec->priv_data, "preset", "slow", 0);

	// now lets  ctually open the codec
	if (avcodec_open2(stream->codec, codec, NULL) < 0) ;//handle errors here

	// end of function -- we have initialize stream and element etc
}
/*
 * Create a valid output context given a file name
 * 
 *  1.) Should parse the string and ensure that we are creating the correct output type
 *
 */
static AVFormatContext * createFormatContext(const char * outputPath, const char * format) {

	av_register_all();

	// initialize a null pointer to the output context
	AVFormatContext * output = NULL;
	
	// now lets initialize the actual format element
	if (avformat_alloc_output_context2(&output, NULL, format, outputPath) < 0) {

		// handle errors with elegance here!
	}
	
	// return context that was created
	return output;
}



/* Steps: 
 * 
 * 1.) get a format context for input file
 * 2.) create a pointer to the video stream etc
 * 3.) initialize the codec for output 
 * 4.) Loop through each frame and encode into the output file etc
 *
 */
static void encodeVideo(EncodingJob * encodingJob) {

	av_register_all();
	
	
	
	/* 
	 *	Initialize decoder methods and objects on the heap
	 *
	 */
	// this is going to open the input file and give us a handle to grab the streams etc that we want from it
	AVFormatContext * inputContext = decode.getFormatContext(encodingJob->inputPath);

	// cache the index of hte video stream for the input element
	int videoStreamIndex = decode.getVideoStreamIndex(inputContext);

	// create elements needed for decoding stream 			
	AVStream const *const inStream = inputContext->streams[videoStreamIndex];	

	// initialize decoder codec
	AVCodec * const decoder = avcodec_find_decoder(inStream->codec->codec_id);

	// now ensure that our decoder is valid
	if (!decoder) ;//handle error nicely

	// now make sure we can easily open the codec		
	if (avcodec_open2(inStream->codec, decoder, NULL) < 0) ;//handle error

	/*
	 * Now initialize encoder for output of the video 
	 *
	 */
	// now lets initialize the avformatcontext for the output container
	AVFormatContext * outputContext = createFormatContext(encodingJob->outputPath, encodingJob->outputFormat);

	// change this in the future so that we can switch up the elements for encoding
	AVCodec * encoderCodec = NULL;// avcodec_find_encoder(3333);
	AVStream * outStream = NULL;
	
	// pass the encoder and outputStream into the element
	initializeCodec(&encoderCodec, &outStream, outputContext, encodingJob);

	// our codec is now properly initialized and opened
	// open the stream needed
	if(avio_open(&outputContext->pb, encodingJob->outputPath, AVIO_FLAG_WRITE) < 0) ;//handle error elegantly here

	// now lets start to actually decode the stream and re-encode it into the next step
		

}

// now implement the namespace struct that was initialized as an external variable in previous header
encode_namespace const encode = {.encodeVideo = encodeVideo, .createFormatContext = createFormatContext};

