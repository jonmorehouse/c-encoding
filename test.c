#include <libavcodec/avcodec.h>
#include "decode.h"

int main(int argc, char * argv[]) {

	char * const filePath = "test";
	decode.fromPath(filePath);

	return 0;
}
