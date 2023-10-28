CC = gcc
flags = -Wall -g
ENDFLAGS = -lcunit -lm -o

LIB_DIR := C_hash/lib
INCLUDE := C_hash/include

read.o: reader_test.c LIBRARY
	${CC} ${flags} $< utils.c -lhash -L${LIB_DIR} -I${INCLUDE} ${ENDFLAGS} $@

LIBRARY:
	make -C C_hash

