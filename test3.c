#include <stdio.h>
#include "hawk.h"

int main (void) {
	hawk h = {};

	static char line[1<<20] = {};

	long accum = 0;

	while(fgets(line, sizeof(line), stdin) && hawk_nextline(&h,line)) {

		long first = hawk_int(&h, 0);


		if(first > 1) {
			accum += first;
			puts(h.rline);
		}

	}

	printf("%li\n",accum);
}

