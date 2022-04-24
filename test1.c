#include <stdio.h>
#include "hawk.h"

int main (void) {
	hawk h = {};

	static char line[1<<20] = {};

	while(fgets(line, sizeof(line), stdin) && hawk_nextline(&h,line)) {

		printf("Line: %s\n", h.rline);
		for(int i = 0; i < h.NF; i++){
			printf("Field '%s'\n", hawk_str(&h, i));
			if(i == 0) printf("Numeric value: %f\n", hawk_anum(& h,i));
			if(i == 0) printf("Integer value: %li\n", hawk_aint(& h,i));
		}

	}
}
