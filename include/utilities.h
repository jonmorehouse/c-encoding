#ifndef UTILITIES_H
#define UTILITIES_H

typedef struct {

	// take in an immutable string pointer
	// return an immutatable string point
	const char * (* const getFormatFromPath)(const char *);

} utilities_namespace;

// now lets declare an external variable that can be accessed 
extern utilities_namespace const utilities;

#endif
