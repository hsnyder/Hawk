#include <stdio.h>
#include "hawk.h"

int main (void) {
	hawk h = {.FS_tag=HAWK_LITERAL, .FS=":|:"};

	static char line[1<<20] = {};

	while(fgets(line, sizeof(line), stdin) && hawk_nextline(&h,line)) {

		printf("Line: %s\n", h.rline);
		for(int i = 0; i < h.NF; i++){
			printf("Field '%s'\n", hawk_str(&h, i));
		}

	}
}
