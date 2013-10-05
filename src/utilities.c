#include "utilities.h"
#include <stdio.h>
#include <string.h>

static const char * getFormatFromPath(const char * inputPath) {
	
	// initialize format element
	const char * format;

	// now initialize temp strings for use throughout function
	char * token,  * string, * tofree;
	
	// now initialize a few elements
	tofree = string = strdup(inputPath);

	// loop through each of the elements
	while ((token = strsep(&string, ".")) != NULL) 
		format = token;

	// now free the temporary memory
	free(tofree);

	return format;
}

// now lets export this function that we just created into the utilities namespace
utilities_namespace const utilities = {.getFormatFromPath = getFormatFromPath};

