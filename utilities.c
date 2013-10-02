#include "utilities.h"
#include <stdio.h>

static const char * getFormatFromPath(const char * inputPath) {
	
	// initialize format element
	const char * format;

	// now initialize temp strings for use throughout function
	char * token;
	char * string;
	char * tofree;

	// initialize the starting string 
	/*string = strdup(inputPath);*/
	string = strdup("abc,def,ghi");

	// 
	if (string != NULL) {

		// iniitalize element
		tofree = string;

		// loop through the string pieces
		while ((token = strsep(string, ",")) != NULL) {

			// cache the token 		
			/*printf("%s\n", token);*/

		}
		
		// 
		free(tofree);

	}//end of master if


	format = "test";
	return format;
}

// now lets export this function that we just created into the utilities namespace
utilities_namespace const utilities = {.getFormatFromPath = getFormatFromPath};




