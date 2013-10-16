#include "output.h"

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
static Output * OutputInit(const EncodingJob * encodingJob, const Input * input) {
	
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

	int status;

	// open the output file if necessary
	if (!(job->format->flags & AVFMT_NOFILE)) {

		status = avio_open(&job->context->pb, encodingJob->outputPath, AVIO_FLAG_WRITE);

		if (status != 0) ;// unable to open the context, things aren't working correctly
	}

	// now write the correc headers to this file as needed
	if (avformat_write_header(job->context, NULL) < 0) {
		
		// handle errors nicely in this block
	}

	// initailize the resize context using the input / output parameters
	// http://stackoverflow.com/questions/12831761/how-to-resize-a-picture-using-ffmpegs-sws-scale
	job->resizeContext = sws_getContext(input->videoCodecContext->width, input->videoCodecContext->height, 
			input->videoCodecContext->pix_fmt, job->videoCodecContext->width, 
			job->videoCodecContext->height, job->videoCodecContext->pix_fmt,
			SWS_BICUBIC, NULL, NULL, NULL);

	// check to ensure that we created the job resizing context correctly
	if (!job->resizeContext) ;//handle errors here

	// now we need to create a frame for allocating the elemnets into
	job->frame = avcodec_alloc_frame();

	// ensure that we crate the frame needed successfully
	if (!job->frame) ;// handle errors here with elegance

	// now lets allocate the correct amount of data needed for the frame 2 container
	job->frameBufferSize = avpicture_get_size(job->videoCodecContext->pix_fmt, job->videoCodecContext->width, job->videoCodecContext->height);

	// initialize and build out our frame buffer on the heap
	job->frameBuffer = (uint8_t *)av_malloc(job->frameBufferSize * sizeof(uint8_t));

	// now lets fill the picture and link up the element with this
	// this avpicture fill is used to set up the element with the correct frame buffer
	avpicture_fill((AVPicture*)job->frame, job->frameBuffer, job->videoCodecContext->pix_fmt, job->videoCodecContext->width, job->videoCodecContext->height);

	// return the new output pointer
	return job;
}

static void OutputClose(Output * job) {

	av_write_trailer(job->context);

	return;
	
	// now make sure we can safely close the file
	if (!(job->context->oformat->flags & AVFMT_NOFILE)) {

		avio_close(job->context->pb);
	}

	return;
	// write any headers needed
	// remove the packet if it exists
	if (job->packet) av_free_packet(job->packet);

	// now lets see if the frame exists and clear that if necessary
	if (job->frame) avcodec_free_frame(job->frame);
	
	// deallocate memory as needed
	avcodec_close(job->audioCodecContext);
	avcodec_close(job->videoCodecContext);

	// nowclose the avf
	// now close the various codec contexts
	avformat_free_context(job->context);

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
	// print out the dts element etc
	if (input->packet->stream_index == AVMEDIA_TYPE_VIDEO) {

		// decode the video->packet into the video->frame
		decode.decodeVideo(input);

		// continue because we didn't get a full frame
		if (input->gotFrame) {

			// now output video properly with the correct encoding elements
			write.writeVideoFrame(input, job);
		}
	}

	// now lets take the packet stream index element 
	else if (input->packet->stream_index == AVMEDIA_TYPE_AUDIO) {

	
		// decode the input->packet into the input->frame
		decode.decodeAudio(input);

		// make sure that we got a frame from the packet
		if (input->gotFrame) {

			// now lets call the correct output audio function
			write.writeAudioFrame(input, job);	
		}
	}
}

// output element
output_namespace const output = {

	// create output format context
	.createFormatContext = createFormatContext,

	// allocation / deallocation of dynamic output struct
	.OutputInit = OutputInit,
	.OutputClose = OutputClose,
	
	// create a packet handler
	.packetHandler = packetHandler, 

};
