#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

#include <stdio.h>

int main() {

	av_register_all();

	AVFormatContext * output = NULL;
	
	// now lets initialize the actual format element
	if (avformat_alloc_output_context2(&output, NULL, "mp4", "test.mp4") < 0) {

		// handle errors with elegance here!
		printf("%s", "INVALID");
	}

	return 0;

}




