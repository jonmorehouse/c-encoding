#include "common.h"
#include "decode.h"
#include "encode.h"
#include "utilities.h"
#include "output.h"

// now include any project dependencies
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <stdio.h>



void testGetFormatFromPath() {

	const char * inputPath = "test.mov";
	const char * format;

	format = utilities.getFormatFromPath(inputPath);

}

// run through and encode a job
void testEncoding(EncodingJob * encodingJob) {

	encode.encodeVideo(encodingJob);
}

void testOutput(EncodingJob * encodingJob) {
	
	Output * outputJob = output.OutputInit(encodingJob);

}

int main(int argc, char * argv[]) {

	// initialize an encoding job and the pieces that are needed for it!
	static char * const inputPath = "fixtures/sample-clip.mp4";
	static char * const outputPath = "fixtures/output.mp4";
	static char * const format = "mpegts";

	// initialize the encoding job
	EncodingJob encodingJob = { 
		
		.inputPath = inputPath, 
		.outputPath = outputPath, 
		.outputFormat = format,
		
		.codecId = AV_CODEC_ID_MPEG1VIDEO, 

		.videoBitrate = 200000, 
		.height = 300, 
		.width = 400, 

		.fps = {
			.num = 29970,
			.den = 1000,
		},

		.gop_size = 12,

		.audioBitrate = 64000, 
		.sampleRate = 44100
	};

	// run a test encoding job	
	testEncoding(&encodingJob);

	// 
	return 0;
}







