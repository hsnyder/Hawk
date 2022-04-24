#ifndef HAWK_H
#define HAWK_H

#include <stddef.h>

enum {
	HAWK_MAX_LINE = 2400,
};

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

	long NR;  // init to zero, read only
	long NF;  // init to zero, read only

	hawk_septype FS_tag; // user initialize
	char FS[20];         // user initialize

	void (*error_callback) (const char *);
	char  rline[HAWK_MAX_LINE];
	char  mline[HAWK_MAX_LINE];
	short f[HAWK_MAX_LINE];


} hawk;

typedef struct hawk_pattern {

	int is_valid;

} hawk_pattern;

hawk_pattern hawk_mkpattern(const char * str);

// 'strong type' version, do actual type checking.
hawk_pattern hawk_smkpattern(const char * str);

int hawk_nextline(hawk* h, char * line);

int hawk_matchline(hawk* h, hawk_pattern p);

const char * hawk_strfield(hawk* h, int i);

// don't check type, just use atof style conversions
double hawk_numfield(hawk* h, int i);
long   hawk_intfield(hawk* h, int i);

// assert type
double hawk_anumfield(hawk* h, int i);
long   hawk_aintfield(hawk* h, int i);


#endif
