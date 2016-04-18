all: lstdir rmdup

lstdir: lsdir.c
	gcc lsdir.c -o bin/lsdir -Wall

rmdup: rmdup.c
	gcc rmdup.c -o bin/rmdup -Wall

