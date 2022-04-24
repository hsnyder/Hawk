#ifndef HAWK_H
#define HAWK_H

#include <stddef.h>

enum {
	HAWK_MAX_LINE = 2400,
};

typedef enum hawk_septype {
	HAWK_DEFAULT = 0,
	HAWK_LITERAL,
} hawk_septype;

/*
	User should initialize this struct to zero, except for (optionally):
	- FS_tag
	- FS
	- error_callback

	FS is the field separator, which is a string.
	Currently, two field separator types are supported (specified via FS_tag):

	- HAWK_DEFAULT means to ignore the value of FS and use any amount of adjacent whitespace as the field separator.
	  In this mode, leading spaces are ignored and will not result in an empty field at index 0.

	- HAWK_LITERAL means to use the literal string provided in FS as the field separator.
	  In this mode, all separators are honoured, so if the lines starts with a separator, the first field will be empty.

	If an error callback is not provided, the default action is to print to stderr and terminate.
	  
*/
typedef struct hawk {

	long NR;  // Number of records (number of lines seen thusfar). init to zero, read only
	long NF;  // Number of fields on the current line.             init to zero, read only

	hawk_septype FS_tag; // Field separator type. init to zero or initialize with desired value
	char FS[20];         // Field separator.      init to zero or initialize with desired value

	void (*error_callback) (const char *); // init to zero or initialize with desired value

	char  rline[HAWK_MAX_LINE]; // read only (contains an exact copy of the last input line)
	char  mline[HAWK_MAX_LINE]; // internal use, don't read or write
	short f[HAWK_MAX_LINE];     // internal use, don't read or write


} hawk;


// Ingests a line from a character string and splits it into fields
int hawk_nextline(hawk* h, char * line);






/* 
Returns the (0-based) i-th field from the current line. 
Returns empty if i out of range.
*/
const char * hawk_str(hawk* h, int i);

/* 
Returns the (0-based) i-th field from the current line, interpreted as a double. 
Returns 0.0 if i is out of range, or if the field couldn't be converted.
*/
double hawk_num(hawk* h, int i);


/* 
Returns the (0-based) i-th field from the current line, interpreted as a long. 
Returns 0 if i is out of range, or if the field couldn't be converted.
*/
long   hawk_int(hawk* h, int i);


// The "a" prefix means "assert"
// -----------------------------

/* 
Returns the (0-based) i-th field from the current line. 
Triggers error callback and returns NULL if i out of range.
*/
const char * hawk_astr(hawk* h, int i);

/* 
Returns the (0-based) i-th field from the current line, interpreted as a double.
Triggers error callback and returns 0.0 if i out of range.
*/
double hawk_anum(hawk* h, int i);

/* 
Returns the (0-based) i-th field from the current line, interpreted as a long.
Triggers error callback and returns 0 if i out of range.
*/
long   hawk_aint(hawk* h, int i);


#endif
