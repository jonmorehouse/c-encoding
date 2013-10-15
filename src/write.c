#include "write.h"

static void writeAudioFrame(Input * input, Output * job) {



}

static void writeVideoFrame(Input * input, Output * job) {



}


write_namespace const write = {

	.writeVideoFrame = writeVideoFrame,
	.writeAudioFrame = writeAudioFrame

};
