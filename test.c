#include "decode.h"
#include "encode.h"

// now include any project dependencies
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#include <stdio.h>

void testEncodeCreateOutputContext() {

	// initialize the outputPath
	char * const outputPath = "fixtures/test.mov";
	AVFormatContext * output = NULL;
	
	// now lets call the function properly
	output = encode.createFormatContext(outputPath);
}

void testEncoding() {

	char * const inputPath = "fixtures/sample-clip.mov";
	char * const outputPath = "fixtures/output.ts";
	EncodingJob encodingJob = { .codecId = 1, .bitrate = 200000, .height = 300, .width = 400, .fps = 25.00, .codecId = AV_CODEC_ID_MPEG1VIDEO};

	// call encoding function
}

int main(int argc, char * argv[]) {

	// run output context creation test
	testEncodeCreateOutputContext();

	return 0;
}
