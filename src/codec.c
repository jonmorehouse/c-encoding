#include "codec.h"

// create an output audio codec from the context passed in and encoding job passed in
AVCodec * createAudioCodec(Output * currentOutput, EncodingJob * encodingJob) {
	
	

}

// create a video codec from the formatcontext and encodingjob given
AVCodec * createVideoCodec(Output * currentOutput, EncodingJob * encodingJob) {



}

// export the namespace variable
codec_namespace const codec = {.createAudioCodec = createAudioCodec, .createVideoCodec = createVideoCodec};
