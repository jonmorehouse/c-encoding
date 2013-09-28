#ifndef DECODE_H
#define DECODE_H

// declare a structure to export all of the functions that we are declaring in this namespace etc
typedef struct {

	void (* const fromPath)(const char *);

} namespace_struct;

// declare a structure variable that can be accessed from exterior calling functions
extern namespace_struct const decode;

#endif // ENCODE_H
