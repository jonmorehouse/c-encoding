#include "output.h"

#include <stdio.h>

static void outputAudio(AVPacket * packet, AVFormatContext * output) {
	
	
}


/*
 * Output encoded video to the output context
 *
 *
 *
 *
 */
static void writeVideoFrame(AVPacket * packet, AVFormatContext * outputContext) {
	
	// output video here		
	av_write_frame(outputContext, packet);




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

	// print out the dts element etc
	if (packet->stream_index == AVMEDIA_TYPE_VIDEO) {
	
		// now output video properly with the correct encoding elements
		writeVideoFrame(packet, outputContext);
	}

	// now lets take the packet stream index element 
	else if (packet->stream_index == AVMEDIA_TYPE_AUDIO) {

		// now lets call the correct output audio function
		outputAudio(packet, outputContext);	
	}

}

output_namespace const output = {.packetHandler = packetHandler, .outputVideo = outputVideo};
