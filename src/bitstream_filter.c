#include "bitstream_filter.h"

static void initBitstreamFilters(Output * job) {




}

static void filter(AVPacket * packet, Output * job) {



}

// now create our namespace variable
bitstream_filter_namespace const bitstream_filter = {

	.initBitstreamFilters = initBitstreamFilters,
	.filter = filter
};

