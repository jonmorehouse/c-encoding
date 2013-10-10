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

// initialize an encoding job and the pieces that are needed for it!
static char * const inputPath = "fixtures/sample-clip.mov";
static char * const outputPath = "fixtures/output.mp4";
static char * const format = "mpegts";

/*EncodingJob encodingJob = { .codecId = 1, .bitrate = 200000, .height = 300, .width = 400, .fps = 25.00, .codecId = AV_CODEC_ID_MPEG1VIDEO, .inputPath = inputPath, .outputPath = outputPath, .outputFormat = format};*/
void testGetFormatFromPath() {

	const char * inputPath = "test.mov";

	const char * format;

	// 
	format = utilities.getFormatFromPath(inputPath);

	printf("%s", format);
}

void testEncodeCreateOutputContext() {

	// initialize the outputPath
	char * const outputPath = "fixtures/test.mp4";
	AVFormatContext * output;

	// now lets call the function properly
	output = encode.createFormatContext(outputPath, "mpeg");
}

void testEncoding() {

	encode.encodeVideo(&encodingJob);
}

void testOutput() {
	
	Output * outputJob = output.OutputInit(&encodingJob);

	printf("%i", outputJob->test);

}

int main(int argc, char * argv[]) {

	// run output context creation test
	/*testEncodeCreateOutputContext();*/

	// just test the utilities for now
	/*testGetFormatFromPath();*/

	testOutput();
	/*testEncoding();*/
	//
	return 0;
}







