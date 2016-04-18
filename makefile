CC = gcc

CFL= -Wall

RM = rm -f

all: rmdup.o lsdir.o

rmdup: rmdup.c
	$(CC) $(CFL) -o bin/rmdup rmdup.c

lstdir: lsdir.c
	$(CC) $(CFL) -o bin/lsdir lsdir.c

clean:
	$(RM) bin/*
