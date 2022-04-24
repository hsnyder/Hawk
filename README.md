# Hawk

A small library for writing awk-style programs in C (i.e. pattern-action sequences on line-oriented, delimited text files).

Example:

```
#include <stdio.h>
#include "hawk.h"

int main (void) {

	/*
		- Read stdin line by line
		- Split line into whitespace-delimited fields
		- Interpret the first column as an integer and sum all entries greater than 3.
		- Print out the sum at the end.
	*/

	hawk h = {};
	static char line[1<<20] = {};
	long sum = 0;

	while (fgets(line, sizeof(line), stdin) && hawk_nextline(&h,line)) {

		long f1 = hawk_intfield(&h, 0);

		if (f1 > 3) { sum += f1; }

	}

	printf("%li\n",sum);
}
```
