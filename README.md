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

		long f1 = hawk_int(&h, 0); // get the first field as an integer (zero based index)

		if (f1 > 3) { sum += f1; }

	}

	printf("%li\n",sum);
}
```

## Noteworthy limitations

- Currently all arrays are fixed size, leading to a maximum line length set at compile time.
- Minor gotcha: the library assumes that the line fed to `hawk_nextline` is newline terminated, and it trims off that newline char. If the input line isn't newline terminated, then the last (potentially valid) char will get clipped off.

## Future work

- Fix things in "noteworthy limitations".
- Implement character-class field separators (e.g. split on ' ' or ',').
- (?) Implement regular expression field separators.
- (?) Hide/encapsulate members of the `hawk` struct that are intended for internal use only.
- Add a third variant of the field accessor methods that allows the user to detect an invalid type or out of range field index without firing off the error callback. The error callback is useful when the programmer wants to print a message and bail on parsing the line, but if a type error in the data should be considered non-fatal, it's not the most convenient mechanism. 
- Add a mode for ingesting TSV data.
- Add a mode for ingesting CSV data.
