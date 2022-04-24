#include <stdio.h>
#include "hawk.h"

int main (void) {
	hawk h = {};

	static char line[1<<20] = {};

	while(fgets(line, sizeof(line), stdin) && hawk_nextline(&h,line)) {

		printf("Line: %s\n", h.line);
		for(unsigned i = 0; i < h.NF; i++){
			printf("Field '%s'\n", h.flds[i]);
		}

	}
}
