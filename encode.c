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
	
	// this is going to open the input file and give us a handle to grab the streams etc that we want from it
	AVFormatContext * inputContext = decode.getFormatContext(encodingJob->inputPath);
	
	// now lets initialize the avformatcontext for the output container
	AVFormatContext * outputContext = createFormatContext(encodingJob->outputPath, encodingJob->outputFormat);
	
	// cache the index of hte video stream for the input element
	int videoStreamIndex = decode.getVideoStreamIndex(inputContext);

	printf("%i", videoStreamIndex);
	
	// create elements needed for decoding stream 			
	/*AVStream const *const inStream = inputContext->streams[	*/

}

// now implement the namespace struct that was initialized as an external variable in previous header
encode_namespace const encode = {.encodeVideo = encodeVideo, .createFormatContext = createFormatContext};

