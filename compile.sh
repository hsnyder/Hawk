#!/usr/bin/env sh
CFLAGS="-Wall -Wextra -Wswitch-enum"
cc $CFLAGS hawk.c re.c test1.c -o test1
cc $CFLAGS hawk.c re.c test2.c -o test2
cc $CFLAGS hawk.c re.c test3.c -o test3
