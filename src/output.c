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

	// now generate the audio / video codec as needed
	// this will open the codec
	codec.createAudioCodec(job, encodingJob);

	// create the video output codec
	// this will open codec and do a few things to the stream
	codec.createVideoCodec(job, encodingJob);

	/* Create bitstream filters */
	bitstream_filter.initBitStreamFilters(job);

	// now lets open both codecs 
	// open audio codec
	codec.openCodec(job, AVMEDIA_TYPE_AUDIO);

	// open video codec
	codec.openCodec(job, AVMEDIA_TYPE_VIDEO);

	// now that we have opened out codecs etc we need to write the correct headers
	av_dump_format(job->context, 0, encodingJob->outputPath, 1);

	// open the output file if necessary
	if (!(job->format->flags & AVFMT_NOFILE)) {

		if (avio_open(&job->context->pb, encodingJob->outputPath, AVIO_FLAG_WRITE) < 0 )
			printf("%s""\n", "Could not open filename"); 
	}

	// now write the correc headers to this file as needed
	if (avformat_write_header(job->context, NULL) < 0) {
		
		// handle errors nicely in this block
	}

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
	/*bitstream_filter.filter(&packet, job, AVMEDIA_TYPE_VIDEO);*/
	int ret;
	static struct SwsContext * sws_ctx;
	AVCodecContext * c = job->videoStream->codec;
	
	/*printf("size: " "%i" "\n", packet->size);*/
	/*printf("dts: " "%i" "\n", packet->dts);*/
	/*printf("pts: " "%i" "\n", packet->pts);*/

	ret = av_interleaved_write_frame(job->context, packet);
	printf("return: " "%i" "\n", ret);

}


/*
 * Packet handler is responsible for taking in an output context and then a packet and then doing magical shit!!
 *
 * 1.) check to see if the data  exists
 * 2.) check to see if the output is audio or video
 * 3.) send the packet to the correct function audio/video etc
 *
 */
static void packetHandler(Input * input, Output * job) {

	// now lets ensure that we have the correct size for the input buffer
	// resize the input buffer here
	// also assume that the input buffer is cleared out
	if (input->bufferSize < input->packet->size) {

		input->bufferSize = input->packet->size;
		input->buffer = (uint8_t *)realloc(input->buffer, input->bufferSize * sizeof(uint8_t));
	}
	
	// print out the dts element etc
	if (input->packet->stream_index == AVMEDIA_TYPE_VIDEO) {

		// decode the audio stream into a raw packet
		decode.decodeVideo(input);

		// now output video properly with the correct encoding elements
		/*writeVideoFrame(input->packet, job);*/
	}

	// now lets take the packet stream index element 
	else if (input->packet->stream_index == AVMEDIA_TYPE_AUDIO) {
	
		// decode the audio into a raw method
		decode.decodeAudio(input);

		// now lets call the correct output audio function
		/*writeAudioFrame(input->packet, job);	*/
	}

}

// output element
output_namespace const output = {

	// create output format context
	.createFormatContext = createFormatContext,
	.OutputInit = OutputInit,
	
	// create a packet handler
	.packetHandler = packetHandler, 
	.writeAudioFrame = writeAudioFrame, 
	.writeVideoFrame = writeVideoFrame

};
