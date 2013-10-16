#include "utilities.h"
#include "encode.h"
#include "output.h"

// now include erroneous, temp libraries here
#include <stdio.h>

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
	/*AVFormatContext * inputContext = decode.getFormatContext(encodingJob->inputPath);*/
	Input * input = decode.InputInit(encodingJob->inputPath);

	// initialize the output element
	Output * job = output.OutputInit(encodingJob, input);

	// initialize a packet on the stack for quicker reference
	AVPacket packet;
	input->packet = &packet;

	// now read the entire input file in a while loop!
	while(av_read_frame(input->context, input->packet) >= 0) {

		// handle the encoding elements etc
		output.packetHandler(input, job);
	
		// we will decode the packet in the proper places in the output function
		// keep this method as light as possible!
		av_free_packet(input->packet);
	}

	// close both input and output
	output.OutputClose(job);
	/*decode.InputClose(input);*/
}

// now implement the namespace struct that was initialized as an external variable in previous header
encode_namespace const encode = {

	.encodeVideo = encodeVideo, 
	
};

