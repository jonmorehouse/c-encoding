#include "stream.h"

static AVStream * createStream(AVFormatContext * context, AVCodec ** codec, enum AVCodecID codecId) {

	
}

stream_namespace const stream = {

	.createStream = createStream,

};
