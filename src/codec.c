#include "codec.h"

// select high sample rate for creation in codec
int selectSampleRate(AVCodec * codec) {

	const int *iterator;
	int bestSampleRate = 0;

	// if no codec supported samplerates
	if (!codec->supported_samplerates)
		return 44100;

	// cache a pointer to the supported samplerates for this codec
	iterator = codec->supported_samplerates;

	// loop through the array
	while (*iterator) {

		// now lets check to see if this samplerate is higher than the previous one
		if (*iterator > bestSampleRate) bestSampleRate = FFMAX(*iterator, bestSampleRate);

		// increase the iterator
		iterator++;
	}

	return bestSampleRate;

}

// return the correct channel 
int selectChannelLayout(AVCodec * codec) {

	// create a pointer to the codec channels array
	const uint64_t * iterator;
	uint64_t bestChannelLayout = 0;
	int bestNumberChannels = 0;

	// now lets see if there is no channel layouts etc
	// if there aren't any channel layouts just use stereo
	if (!codec->channel_layouts) return AV_CH_LAYOUT_STEREO;

	// cache the iterator
	iterator = codec->channel_layouts; 

	// loop through the aray of channel layouts 
	while (*iterator) {

		// get the number of channels for this particular layout
		int numberChannels = av_get_channel_layout_nb_channels(*iterator);

		if (numberChannels > bestNumberChannels) {

			// grab the current dereferenced value
			bestChannelLayout = *iterator;

			// best number of channels etc
			bestNumberChannels = numberChannels;
		}

		// now increase the iterator
		iterator++;
	}

	return bestChannelLayout;
}

// open codec based upon input type
void openCodec(Output * job, enum AVMedia_Type * type) {

	// initialize some temp pointers for the necessary pieces of opening the video codec 
	AVCodec * codec = NULL;
	AVStream * stream = NULL;
	AVCodecContext * codecContext = NULL;
	
	// check status of codec opening
	int codecStatus;

	// now use some audio/video logic to generate the correct streams etc 
	if (type == AVMEDIA_TYPE_AUDIO) {

		stream = job->audioStream;
		codec = job->audioCodec;

	} else {

		stream = job->videoStream;
		codec = job->videoCodec;
	}

	// now ensure that we have a valid stream initialized 
	// now lets grab the correct codec context
	// http://ffmpeg.org/doxygen/trunk/structAVCodecContext.html
	codecContext = stream->codec;
	
	// now we need to open our video
	codecStatus = avcodec_open2(codecContext, codec, NULL); 	

	// ensure that the codec is opened properly
	if (codecStatus < 0) printf("%s" "\n", av_err2str(codecStatus));
}

// create an output audio codec from the context passed in and encoding job passed in
static void createAudioCodec(Output * job, EncodingJob * encodingJob) {

	/*** Initialize proper data structures for elements ****/
	// codecID is generated from the format
	enum AVCodecID codecID = job->format->audio_codec;

	// initialize the audio context etc
	AVCodec ** codec = &job->audioCodec;
	// intiialize a pointer that is linked to the output element
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
	if (!*stream) printf("%s", "no stream");//handle errors nicely

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
	(*codecContext)->sample_rate = selectSampleRate(*codec);
	
	// we normally use 2 channels for audio 
	(*codecContext)->channel_layout = selectChannelLayout(*codec);

	// grab the correct number of channels based upon the best selected audio channel layout
	(*codecContext)->channels = av_get_channel_layout_nb_channels((*codecContext)->channel_layout);

	// now lets see if format wants stream headers to be seperate etc
	if (job->context->flags && AVFMT_GLOBALHEADER)
		(*codecContext)->flags |= CODEC_FLAG_GLOBAL_HEADER;

}

// create a video codec from the formatcontext and encodingjob given
static void createVideoCodec(Output * job, EncodingJob * encodingJob) {

	/**** Initialize data structures to assist with stream creation ***/ 
	enum AVCodecID codecID = job->format->video_codec;

	// initialize audio context 
	AVCodec ** codec = &job->videoCodec;	
	AVCodecContext ** codecContext = &job->videoCodecContext;
	AVStream ** stream = &job->videoStream;

	/*** Initialize Encoder ***/	

	// make sure that we have a format codec linked up
	if (codecID == AV_CODEC_ID_NONE) ;//handle errors here

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

	// fixed this issue without any major hickups
	/*(*codecContext)->bit_rate_tolerance = 8000;*/

	// now copy over the various trivial assets / figures over
	(*codecContext)->width = encodingJob->width;
	(*codecContext)->height = encodingJob->height;

	// set pixel format needed for this element
	(*codecContext)->pix_fmt = AV_PIX_FMT_YUV420P; // initialize pixel format

	// now initialize frame rate elements
	// note that for fixed frame rate video time_base = fps/1
	(*codecContext)->time_base.num = encodingJob->fps.num;
	(*codecContext)->time_base.den = encodingJob->fps.den;

	// initialize gop_size 
	(*codecContext)->gop_size = encodingJob->gop_size;

	// set frame rate tolerance
	(*codecContext)->bit_rate_tolerance = 256000;

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
codec_namespace const codec = {
	
	// helper utilities
	.selectChannelLayout = selectChannelLayout,
	.selectSampleRate = selectSampleRate,

	// create audio codecs
	.createAudioCodec = createAudioCodec, 
	.createVideoCodec = createVideoCodec,

	// now actually open the codec correctly
	.openCodec = openCodec

};
