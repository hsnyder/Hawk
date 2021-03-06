#include "hawk.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>




static void 
hawk_err(hawk * h, const char * msg) 
{
	if (h->error_callback) {
		h->error_callback(msg);
	} else {
		fputs(msg,stderr);
		fputc('\n',stderr);
		exit(EXIT_FAILURE);
	}
}

int
hawk_nextline(hawk * h, char * line)
{
	const long len = strlen(line)-1; // minus one to get rid of the newline character
	const long linemax = sizeof(h->rline);
	
	if (len >= linemax) {
		hawk_err(h, "Hawk: input line too long.");
		return 0;
	}

	memset(h->rline, 0, sizeof(h->rline));
	memset(h->mline, 0, sizeof(h->mline));
	memset(h->f, 0, sizeof(h->f));

	memcpy(h->rline, line, len);
	memcpy(h->mline, line, len);

	h->NF = 0;
	unsigned char in_field = 0;
	int li = 0;

	switch (h->FS_tag) {

	case HAWK_DEFAULT:
		
		while (li < len) {
		
			if (isspace(h->mline[li]) && in_field) {
				in_field = 0;
				h->mline[li++] = 0;
				continue;
			}

			if (!isspace(h->mline[li]) && !in_field) {
				in_field = 1;
				h->f[h->NF++] = li++;
				continue;
			}

			li++;
		}

		break;

	case HAWK_LITERAL:

		if(strlen(h->FS) < 1) hawk_err(h, "Hawk: empty literal field separator.");

		while (li < len) {
			char * nextsep = strstr(h->mline + li, h->FS);

			if (!nextsep) {
				h->f[h->NF++] = li;
				break;
			}

			*nextsep = 0;
			h->f[h->NF++] = li;

			li = (nextsep - h->mline) + strlen(h->FS);
		}

		break;

	}

	h->NR++;

	return 1;
}

const char * 
hawk_str(hawk* h, int i)
{
	if(i >= h->NF) return "";
	return &h->mline[h->f[i]];
}

const char * 
hawk_astr(hawk* h, int i)
{
	if(i >= h->NF) 
	{
		hawk_err(h, "hawk_astr: index out of range.");
		return 0;
	}

	return &h->mline[h->f[i]];
}


double
hawk_num(hawk* h, int i)
{
	return atof(hawk_str(h,i));
}

long
hawk_int(hawk* h, int i)
{
	return atol(hawk_str(h,i));
}

double
hawk_anum(hawk* h, int i)
{
	char * end = 0;
	const char * s = hawk_astr(h,i);
	double out = strtod(s, &end);
	if(end == s) {
		char msg[100] = {};
		snprintf(msg,100,"hawk_anum: Field is not a number: %s", s);
		hawk_err(h,msg);
		return 0.0;
	}
	return out;
}

long 
hawk_aint(hawk* h, int i)
{
	char * end = 0;
	const char * s = hawk_astr(h,i);
	long out = strtol(s, &end, 10);
	if(end == s) {
		char msg[100] = {};
		snprintf(msg,100,"hawk_aint: Field is not a number: %s", s);
		hawk_err(h,msg);
		return 0;
	}
	return out;
}

