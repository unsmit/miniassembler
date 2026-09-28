CC = gcc
CFLAGS = -ggdb -Wall -std=c18

../asm : asm.o parser.o
	${CC} ${CFLAGS} -o ../asm asm.o parser.o

asm.o : asm.c asm.h parser.h
	${CC} ${CFLAGS} -c asm.c

parser.o : parser.c parser.h
	${CC} ${CFLAGS} -c parser.c

clean :
	-rm -f asm.o parser.o ../asm