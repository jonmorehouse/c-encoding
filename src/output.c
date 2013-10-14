#include "output.h"

#include <stdio.h>

/*
 * Create a valid output context given a file name
 * 
 *  1.) Should parse the string and ensure that we are creating the correct output type
 */
static AVFormatContext * createFormatContext(char * outputPath, char * format) {

	// register all codecs needed for application
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

void test(AVFormatContext * context) {
	
	AVCodec * codec;
	AVCodecContext * c;
	AVStream * st;

	av_register_all();

	codec = avcodec_find_encoder(context->oformat->video_codec);

	st = avformat_new_stream(context, codec);	

	c = st->codec;

	avcodec_get_context_defaults3(c, codec);

	printf("%p" "\n", c->codec);
	printf("%p" "\n", codec);

	avcodec_open2(c, codec, NULL);
}

/*
 * Initialize output struct for managing the various segments etc
 *
 */
static Output * OutputInit(const EncodingJob * encodingJob) {
	
	// initialize an output structure on the heap 
	Output * job = malloc(sizeof(Output));
		
	// now initialize the output format context
	job->context = createFormatContext(encodingJob->outputPath, encodingJob->outputFormat);

	// cache our output format
	job->format = job->context->oformat;

	/* Create output streams as needed. Link them up with codec and create the correct codecs */			

	test(job->context);
	return;
	// now generate the audio / video codec as needed
	// this will open the codec
	/*codec.createAudioCodec(job, encodingJob);*/

	// create the video output codec
	// this will open codec and do a few things to the stream
	/*codec.createVideoCodec(job, encodingJob);*/

	// now lets open both codecs 
	// open audio codec
	/*codec.openCodec(job, AVMEDIA_TYPE_AUDIO);*/

	// open video codec
	/*codec.openCodec(job, AVMEDIA_TYPE_VIDEO);*/

	/* Create bitstream filters */
	/*bitstream_filter.initBitStreamFilters(job);*/
	
	// return the new output pointer
	return job;
}



/*
 * Write audio data to the current element
 *
 *
 */
static void writeAudioFrame(AVPacket * packet, AVFormatContext * output) {


}


/*
 * Output encoded video to the output context
 *
 * 1.) We need to apply annexb bitstream filter 
 * 2.) Will expect that we are passing in a stream that needs to be written to as well
 *
 *
 */
static void writeVideoFrame(AVPacket * packet, Output * job) {
	
	// first we need to filter the packet and see if that works!!
	bitstream_filter.filter(&packet, job, AVMEDIA_TYPE_VIDEO);
}


/*
 * Packet handler is responsible for taking in an output context and then a packet and then doing magical shit!!
 *
 * 1.) check to see if the data  exists
 * 2.) check to see if the output is audio or video
 * 3.) send the packet to the correct function audio/video etc
 *
 */
static void packetHandler(AVPacket * packet, Output * job) {

	
	// print out the dts element etc
	if (packet->stream_index == AVMEDIA_TYPE_VIDEO) {
	
		// now output video properly with the correct encoding elements
		writeVideoFrame(packet, job);
	}

	// now lets take the packet stream index element 
	else if (packet->stream_index == AVMEDIA_TYPE_AUDIO) {

		// now lets call the correct output audio function
		writeAudioFrame(packet, job);	
	}
}

output_namespace const output = {

	// create output format context
	.createFormatContext = createFormatContext,
	.OutputInit = OutputInit,
	
	// create a packet handler
	.packetHandler = packetHandler, 
	.writeAudioFrame = writeAudioFrame, 
	.writeVideoFrame = writeVideoFrame

};
