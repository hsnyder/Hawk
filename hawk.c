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
	const size_t len = strlen(line);
	
	if (len >= sizeof(h->line)) {
		hawk_err(h, "Hawk: input line too long.");
		return 0;
	}

	memset(h->flds, 0, sizeof(h->flds));
	memset(h->line, 0, sizeof(h->line));
	memcpy(h->line, line, len);

	h->NF = 0;
	unsigned li = 0; // line index
	unsigned fs = 0; // field start
	unsigned fl = 0; // field length

	const size_t fmaxsz = sizeof(h->flds[0]);

	switch (h->FS_tag) {

	case HAWK_DEFAULT:
		
		while (li < len) {
			

			while (li < len && isspace(h->line[li])) { li++; }

			fs = li;
			fl = 0;

			while (li < len && !isspace(h->line[li])) { li++; fl++; }

			if (fl > 0 && fl < fmaxsz) {
				memcpy(&h->flds[h->NF++], &h->line[fs], fl);
			} else if (fl > 0) {
				hawk_err(h, "Hawk: field too long.");
				return 0;
			}

			if(h->NF > sizeof(h->flds)/sizeof(h->flds[0])) {
				hawk_err(h, "Hawk: too many fields.");
				return 0;
			}
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



