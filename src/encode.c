#include "utilities.h"
#include "encode.h"
#include "output.h"

// now include erroneous, temp libraries here
#include <stdio.h>

/*
 * Initialize the output codec and stream accordingly
 * Open the codec for use, but don't open the stream
 *
 */
static void initializeCodec(AVCodec ** inputCodec, AVStream ** inputStream, const AVFormatContext * context, const EncodingJob * job) {

	// initialize temp helper variables here 
	AVCodec * codec = NULL; 
	AVStream * stream = NULL;	

	// now initialize the codec and stream elements as needed
	*inputCodec = avcodec_find_encoder(AV_CODEC_ID_H264);	

	// cache the input codec element
	codec = *inputCodec;

	// now initialize element	
	*inputStream = avformat_new_stream(context, codec);
	
	// chace the newly created stream for ease of use
	stream = *inputStream;

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

	
	// initialize fps elements
	stream->codec->time_base.den = 25;
	stream->codec->time_base.num = 1;
	stream->codec->keyint_min = 25;
	stream->codec->max_b_frames = 1;
	stream->codec->gop_size = 10;

	/*
	stream->codec->b_frame_strategy = 1;
	stream->codec->scenechange_threshold = 40;
	stream->codec->refs = 6;
	stream->codec->qmin = 0;
	stream->codec->qmax = 0;
	stream->codec->qcompress = 0.6;
	stream->codec->max_qdiff = 4;
	stream->codec->i_quant_factor = 1.4;
	*/

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



/* Steps: 
 * 
 * 1.) get a format context for input file
 * 2.) create a pointer to the video stream etc
 * 3.) initialize the codec for output 
 * 4.) Loop through each frame and encode into the output file etc
 *
 */
static void encodeVideo(EncodingJob * encodingJob) {

	// register all codecs for this application
	av_register_all();
	
	// this is going to open the input file and give us a handle to grab the streams etc that we want from it
	// you don't need a decoder -- the whole point of the format context is that it does all of this for you. Allowing you to read packets which give you pieces of the stream!
	AVFormatContext * inputContext = decode.getFormatContext(encodingJob->inputPath);

	// initialize a packet for registering element
	AVPacket decodedPacket;

	// initialize the output element
	Output * currentOutput = output.OutputInit(encodingJob);

	// now read the entire input file in a while loop!
	while(av_read_frame(inputContext, &decodedPacket) >= 0) {
	
		// handle the encoding elements etc

	}


	/*
	// now write the ending to the file
	av_write_trailer(outputContext);

	// now close the context
	avio_close(outputContext->pb);

	// now free the final frames
	//avcodec_free_frame(&encodeFrame);
	//avcodec_free_frame(&decodedFrame);

	// now free the context
	//avformat_free_context(outputContext);

	// and finally close the input file
	av_close_input_file(inputContext);

*/
}

// now implement the namespace struct that was initialized as an external variable in previous header
encode_namespace const encode = {

	.encodeVideo = encodeVideo, 
	
};

