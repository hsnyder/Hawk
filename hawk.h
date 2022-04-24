#ifndef HAWK_H
#define HAWK_H

#include <stddef.h>

typedef enum hawk_septype {
	HAWK_DEFAULT = 0,
	HAWK_REGEX,
	HAWK_LITERAL,
} hawk_septype;

/*
	User should initialize the FS and FS_tag fields,
	and set the rest to zero.

	After initialization, those same fields CAN be modified,
	but the expected useage is to treat the whole struct as read-only.
*/
typedef struct hawk {

	size_t NR;  // init to zero, read only
	size_t NF;  // init to zero, read only

	hawk_septype FS_tag; // user initialize
	char FS[20];         // user initialize

	char line[2400];
	char flds[40][120];

	void (*error_callback) (const char *);

} hawk;

typedef struct hawk_pattern {

	int is_valid;

} hawk_pattern;

hawk_pattern hawk_mkpattern(const char * str);

// 'strong type' version, do actual type checking.
hawk_pattern hawk_smkpattern(const char * str);

int hawk_nextline(hawk* h, char * line);

int hawk_matchline(hawk* h, hawk_pattern p);

char * hawk_strfield(hawk* h, int i);

// don't check type, just use atof style conversions
double hawk_numfield(hawk* h, int i);
long   hawk_intfield(hawk* h, int i);

// assert type
double hawk_anumfield(hawk* h, int i);
long   hawk_aintfield(hawk* h, int i);


#endif
