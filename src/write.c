#include "write.h"

// write a frame
// assume that the packet was already filtered
static void writeFrame(AVPacket * packet, Output * job, enum AVMedia_Type * type) {

	int encodeResult;	

	/*encodeResult = avcodec_encode_video2r);*/
	


}

write_namespace const write = {
	
	.writeFrame = writeFrame

};
