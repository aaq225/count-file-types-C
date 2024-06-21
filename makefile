CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

countFileTypes:  countFileTypes.o syscalls.o
	gcc ${LFLAGS} -o countFileTypes syscalls.o countFileTypes.o
countFileTypes.o: syscalls.h countFileTypes.c
	gcc ${CFLAGS} countFileTypes.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f countFileTypes
