#ifndef WRITE_H
#define WRITE_H

#include "common.h"
#include "output.h"
#include "decode.h"

// initialize av*
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

// initialize a structure for this namespace 
typedef struct {
	
	void (* const writeVideoFrame)(Input *, Output *);
	void (* const  writeAudioFrame)(Input *, Output *);


} write_namespace;

// create an external variable to hold this namespace
extern write_namespace const write;

#endif //WRITE_H
