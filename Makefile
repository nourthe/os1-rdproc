GIT_VERSION := "$(shell git describe --tags --abbrev=0)"

CC=gcc
CFLAGS=-Wall -pedantic -DVERSION=\"$(GIT_VERSION)\"

#test: rdproc
	#./rdproc -ck

rdproc: main.o rdproc.o rdfile.o
	$(CC) $(CFLAGS) -o rdproc main.o rdproc.o rdfile.o

main.o: main.c rdproc.h
	$(CC) $(CFLAGS) -c main.c

rdproc.o: rdproc.c rdproc.h rdfile.h
	$(CC) $(CFLAGS) -c rdproc.c

rdfile.o: rdfile.c rdfile.h
	$(CC) $(CFLAGS) -c rdfile.c

clean:
	rm rdproc rdproc.o main.o
