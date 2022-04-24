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
	const long len = strlen(line);
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

	case HAWK_REGEX:
		hawk_err(h, "Hawk: regex FS not implemented.");
		return 0;
		break;

	case HAWK_LITERAL:
		hawk_err(h, "Hawk: literal FS not implemented.");
		return 0;
		break;

	}

	h->NR++;

	return 1;
}

const char * 
hawk_strfield(hawk* h, int i)
{
	if(i >= h->NF) 
	{
		hawk_err(h, "hawk_strfield: index out of range.");
		return 0;
	}

	return &h->mline[h->f[i]];
}

