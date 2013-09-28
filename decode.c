#include "decode.h"

// include any erroneous libraries that are just temporary etc
#include <stdio.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

// initialize the function that we are creating
// static global variable or function is seen only in the file its declared in
// http://stackoverflow.com/questions/572547/what-does-static-mean-in-a-c-program
static void fromPath(const char * filePath) {
	
	// allocate memory / pointers etc
	// allocate individual frame structure - note that mov / mpeg4 requires individual frames to be handled together etc
	// avframe describes decoded / raw audio / video data
	// http://ffmpeg.org/doxygen/trunk/structAVFrame.html
	AVFrame * frame; 
	
	// initialize a format context pointer
	AVFormatContext * formatContext = NULL;

	// initialize stream for reading from file buffer
	AVStream * stream;

	// now initialize codec context for storing information about codec etc
	AVCodecContext * codecContext;

	// initialize packet storage container etc
	AVPacket packet;

	// register all codecs available on the system
	av_register_all();

	//create an avframe and set it to defaults
	//avframe describes decoded / raw audio/video data
	frame = avcodec_alloc_frame();
	
	// error handler here etc ... 
	if (!frame) { return 1; }

	// now lets open the file using av_open_input
	if (avformat_open_input(&formatContext, filePath, NULL, NULL) != 0) {

		


	}


	


}

// initialize our constant decode struct for exporting etc
namespace_struct const decode = {fromPath};
