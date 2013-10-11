#include "codec.h"

// create an output audio codec from the context passed in and encoding job passed in
AVCodec * createAudioCodec(Output * job, EncodingJob * encodingJob) {

	/*** Initialize proper data structures for elements ****/

	// codecID is generated from the format
	enum AVCodecID codecID = job->format->audio_codec;

	// initialize the audio context etc
	AVCodec ** codec = &job->audioCodec;
	AVCodecContext ** codecContext = &job->audioCodecContext;
	AVStream ** stream = &job->audioStream;

	/*** Now initialize the correct encoder for the format ***/

	// check to see if the codec is initialized yet
	// normally the codec is already initialized
	// should at least have a codec id so that we know how to initialize the correct elements etc
	if (job->format == AV_CODEC_ID_NONE) ;//handle errors here
	
	// now initialize the codec
	*codec = avcodec_find_encoder(codecID);	

	// check to ensure that the video encoder handles itself properly
	if (!(*codec)) ;// handle errors nicely for encoder creation

	// now create the stream using the output context and the codec that we just initialized
	*stream = avformat_new_stream(job->context, *codec);

	// now ensure that we initialize the stream correctly etc
	if (!*stream) ;//handle errors nicely

	// now lets initialize the stream id according to the context
	// this could be easier, but we want to make sure that if we were to call this later / earlier we would still be good
	(*stream)->id = job->context->nb_streams - 1;

	// now link up the stream codec to the output codec
	*codecContext = (*stream)->codec;

	// now initialize the actual codec elements etc
	(*stream)->id = 1;	

	// signed 16 bit sample 
	// @link http://ffmpeg.org/doxygen/trunk/samplefmt_8h.html
	(*codecContext)->sample_fmt = AV_SAMPLE_FMT_S16;
	
	// bits per second
	(*codecContext)->bit_rate = encodingJob->audioBitrate;

	// audio samples per second
	(*codecContext)->sample_rate = encodingJob->sampleRate;
	
	// we normally use 2 channels for audio 
	(*codecContext)->channels = 2;
	
	// now lets see if format wants stream headers to be seperate etc
	if (job->context->flags && AVFMT_GLOBALHEADER)
		(*codecContext)->flags |= CODEC_FLAG_GLOBAL_HEADER;
}

// create a video codec from the formatcontext and encodingjob given
AVCodec * createVideoCodec(Output * job, EncodingJob * encodingJob) {

	/**** Initialize data structures to assist with stream creation ***/ 
	enum AVCodecID codecID = job->format->video_codec;

	// initialize audio context 
	AVCodec ** codec = &job->videoCodec;	
	AVCodecContext ** codecContext = &job->videoCodecContext;
	AVStream ** stream = &job->videoStream;

	/*** Initialize Encoder ***/	

	// make sure that we have a format codec linked up
	if (job->format == AV_CODEC_ID_NONE) ;//handle errors here

	// now build out the codec encoder
	*codec = avcodec_find_encoder(codecID);

	// if the stream isn't created, then go ahead and throw an error
	if (!(*codec)) ;//handle errors here

	// now create the video stream 
	*stream = avformat_new_stream(job->context, *codec);	

	// note that the context now has one more stream attached to it
	// now iitialize the stream id 
	(*stream)->id = job->context->nb_streams - 1;

	// now cache the codec pointer -- remember this is a pointer to a pointer
	*codecContext = (*stream)->codec;

	// now link up the correct pixel format etc -- this should change in the future
	//grab defaults for the codec given the format we are inputting	
	avcodec_get_context_defaults3(*codecContext, *codec); 		
	
	// now copy over any attributes needed etc
	(*codecContext)->bit_rate = encodingJob->videoBitrate;

	// now copy over the various trivial assets / figures over
	(*codecContext)->width = encodingJob->width;
	(*codecContext)->height = encodingJob->height;

	// set pixel format needed for this element
	(*codecContext)->pix_fmt = AV_PIX_FMT_YUV420P; // initialize pixel format

	// now initialize frame rate elements
	// note that for fixed frame rate video time_base = fps/1
	(*codecContext)->time_base.num = encodingJob->fps.num;
	(*codecContext)->time_base.num = encodingJob->fps.den;

	// initialize gop_size 
	(*codecContext)->gop_size = encodingJob->gop_size;

	// now initialize any further elements needed for creating the stream
	// manual switches for mpeg2ts
	if ((*codecContext)->codec_id == AV_CODEC_ID_MPEG2VIDEO)	
		(*codecContext)->max_b_frames = 2;

	// switch for mpeg1video to ensure that we have macro blocks controlled
	if ((*codecContext)->codec_id == AV_CODEC_ID_MPEG1VIDEO)
		(*codecContext)->mb_decision = 2;

	// now initialize the stream  headers if necessary
	if (job->format->flags && AVFMT_GLOBALHEADER)
		(*codecContext)->flags |= CODEC_FLAG_GLOBAL_HEADER;
}

// export the namespace variable
codec_namespace const codec = {.createAudioCodec = createAudioCodec, .createVideoCodec = createVideoCodec};
