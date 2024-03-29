#include "write.h"

static void writeAudioFrame(Input * input, Output * job) {

}

static void writeVideoFrame(Input * input, Output * job) {

	// cache a results integer for evaluating various api calls
	int result; 
	int gotPacket;
	AVPacket packet = { 0 };

	// initialize a new packet for this information
	av_init_packet(&packet);

	// first, we want to rewrite the input frame into our output frame using the correct context
	// this will copy the data from the input frame into the output frame with the correct stream context
	// scale the image into the new frame
	result = sws_scale(job->resizeContext, input->frame->data, input->frame->linesize, 
		0, input->videoCodecContext->height, job->frame->data, job->frame->linesize);

	// there was an error handle accordingly
	if (result <= 0) {

		// handle error accordingly
		return;
	}

	// note that we are not really going to worry about writing raw images into the format containers. We are going to 
	result = avcodec_encode_video2(job->videoCodecContext, &packet, job->frame, &gotPacket);	

	// if the size is zero, then the image was buffered properly into the packet 
	if (!result && gotPacket && packet.size) {

		// set the stream index properly
		packet.stream_index = job->videoStream->index;

		// resample pts here!
		/*packet.pts = av_rescale_q();*/

		int64_t dts, pts;
		int64_t newDts, newPts;

		newPts = av_rescale_q(packet.pts, job->videoCodecContext->time_base, job->videoStream->time_base);

		printf("%" PRIu64 "\n", packet.pts);
		printf("%" PRIu64 "\n", newPts);

		packet.pts = newPts;
		// now write the interlaved ppacket
		// should be 0 on success
		result = av_interleaved_write_frame(job->context, &packet);

	} else {

		result = 0;
	}

	// now ensure that the result was 0
	if (result != 0) {
		
		// handle an error here	

	} else {


	}
}

write_namespace const write = {

	.writeVideoFrame = writeVideoFrame,
	.writeAudioFrame = writeAudioFrame

};
