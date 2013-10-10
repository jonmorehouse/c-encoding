#include "codec.h"

// create an output audio codec from the context passed in and encoding job passed in
AVCodec * createAudioCodec(Output * job, EncodingJob * encodingJob) {
	
	// check to see if the codec is initialized yet
	if (job->format != AV_CODEC_ID_NONE) {
		
		// 
		printf("%s", "PEASANT");	
		
	}

}

// create a video codec from the formatcontext and encodingjob given
AVCodec * createVideoCodec(Output * currentOutput, EncodingJob * encodingJob) {



}

// export the namespace variable
codec_namespace const codec = {.createAudioCodec = createAudioCodec, .createVideoCodec = createVideoCodec};
