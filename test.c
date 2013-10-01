#include "decode.h"
#include "encode.h"

// now include any project dependencies
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#include <stdio.h>

int main(int argc, char * argv[]) {

	char * const inputPath = "fixtures/sample-clip.mov";
	char * const outputPath = "fixtures/output.ts";
	EncodingJob encodingJob = { .codecId = 1, .bitrate = 200000, .height = 300, .width = 400, .fps = 25.00, .codecId = AV_CODEC_ID_MPEG1VIDEO};
	// initialize an input context etc
	AVFormatContext * inputContext = NULL;	

	// now actually grab the context
	inputContext = decode.getFormatContext(inputPath);

	// now that we have the context figured out ... lets get the video stream index

	return 0;
}
