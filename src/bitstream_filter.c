#include "bitstream_filter.h"

static void initBitStreamFilters(Output * job) {
	
	avfilter_register_all();
	// cache filter name
	const char * filterName = "h264_mp4toannexb";
	/*const char * filterName = "mjpeg2jpeg";*/

	// now cache the results of the previous call in the job
	AVBitStreamFilterContext * bsfc = av_bitstream_filter_init(filterName); 

	// now store the pointer in the job -- only if it was properly built out
	if (bsfc)
		job->bitStreamFilterContext = bsfc;

}

static void closeBitStreamFilters(Output * job) {
	
	if (job->bitStreamFilterContext) 
		av_bitstream_filter_close(job->bitStreamFilterContext);
}

static void filter(AVPacket ** inputPacket, Output * job, enum AVMediaType type) {
		
	// cache input packet location
	// remember we actually want to change the packet location that was passed in to us here 
	AVBitStreamFilterContext * filterContext = job->bitStreamFilterContext;
	AVPacket * packet = *inputPacket;	
	AVCodecContext * codecContext = NULL;// need to cache which codec context we are filtering for

	// initialize our codecContext element
	if (type == AVMEDIA_TYPE_AUDIO) codecContext = job->audioCodecContext;
	else codecContext = job->videoCodecContext;
	
	while (filterContext) {

		// initialize current packet
		AVPacket newPacket = *packet;

		// now filter the video
		int filterResult = av_bitstream_filter_filter(filterContext, codecContext, NULL,

				&newPacket.data, &newPacket.size, 
				packet->data, packet->size,
				packet->flags & AV_PKT_FLAG_KEY);

		printf("%i", filterResult);
		printf("%s", "\n");

		// now switch over the filter context
		filterContext = filterContext->next;
	}



}

// now create our namespace variable
bitstream_filter_namespace const bitstream_filter = {

	.initBitStreamFilters = initBitStreamFilters,
	.closeBitStreamFilters = closeBitStreamFilters,
	.filter = filter
};

