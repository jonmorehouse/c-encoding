#include "output.h"

#include <stdio.h>

/*
 * Create a valid output context given a file name
 * 
 *  1.) Should parse the string and ensure that we are creating the correct output type
 *
 */
static AVFormatContext * createFormatContext(const char * outputPath, const char * format) {

	// 
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

static Output * OutputInit(const EncodingJob * encodingJob) {

	

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
static void writeVideoFrame(AVPacket * packet, AVFormatContext * outputContext) {

	// initialize the output bitstream filter context here
	AVBitStreamFilterContext *bitstreamFilterContext = NULL; //outputStream->bitstream_filters;

	// output 		
	av_interleaved_write_frame(outputContext, packet);

}


/*
 * Packet handler is responsible for taking in an output context and then a packet and then doing magical shit!!
 *
 * 1.) check to see if the data  exists
 * 2.) check to see if the output is audio or video
 * 3.) send the packet to the correct function audio/video etc
 *
 */
static void packetHandler(AVPacket * packet, AVFormatContext * outputContext) {

	writeVideoFrame(packet, outputContext);
	// print out the dts element etc
	if (packet->stream_index == AVMEDIA_TYPE_VIDEO) {
	
		// now output video properly with the correct encoding elements
		/*writeVideoFrame(packet, outputContext);*/
	}

	// now lets take the packet stream index element 
	else if (packet->stream_index == AVMEDIA_TYPE_AUDIO) {

		// now lets call the correct output audio function
		/*writeAudioFrame(packet, outputContext);	*/
	}

}

output_namespace const output = {

	// create output format context
	.createFormatContext = createFormatContext,
	
	// create a packet handler
	.packetHandler = packetHandler, 
	.writeAudioFrame = writeAudioFrame, 
	.writeVideoFrame = writeVideoFrame

};
